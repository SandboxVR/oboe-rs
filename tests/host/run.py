#!/usr/bin/env python3
"""Run the real Oboe error callback / FilterAudioStream lifetime test on a host."""
import os
import resource
from pathlib import Path
import subprocess
import tempfile

resource.setrlimit(resource.RLIMIT_CORE, (0, 0))

root = Path(__file__).resolve().parents[2]
src = root / 'sys/oboe/src'
common = ['AdpfWrapper', 'AudioStream', 'AudioSourceCaller', 'DataConversionFlowGraph',
          'FilterAudioStream', 'FixedBlockAdapter', 'FixedBlockReader', 'FixedBlockWriter',
          'SourceFloatCaller', 'SourceI16Caller', 'SourceI24Caller', 'SourceI32Caller',
          'Utilities', 'QuirksManager', 'OboeExtensions', 'Trace', 'Version']
files = [root / 'tests/host/filter_lifetime.cpp', src / 'aaudio/AAudioLoader.cpp']
files += [src / 'common' / (name + '.cpp') for name in common]
files += sorted((src / 'flowgraph').rglob('*.cpp'))
with tempfile.TemporaryDirectory(prefix='oboe-lifetime-') as tmp:
    binary = Path(tmp) / 'test'
    subprocess.run([os.environ.get('CXX', 'clang++'), '-std=c++17', '-g', '-O1',
                    '-fsanitize=address,undefined', '-fno-omit-frame-pointer', '-pthread',
                    '-I' + str(root / 'tests/host/include'),
                    '-I' + str(root / 'sys/oboe/include'), '-I' + str(src),
                    '-include', str(root / 'tests/host/include/platform.h'),
                    *map(str, files), '-o', str(binary)], check=True)
    subprocess.run([str(binary)], check=True)
    regression = subprocess.run([str(binary), '--disable-parent-retention'], capture_output=True, text=True)
    assert regression.returncode != 0 and 'FilterAudioStream destroyed' in regression.stderr, regression
    print('PASS: removing parent retention reproduces the lifetime failure')
