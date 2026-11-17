#!/usr/bin/env python3
"""Compare checked-in Rust storage layouts with actual NDK C++ layouts."""
import os
from pathlib import Path
import re
import subprocess

root = Path(__file__).resolve().parents[1]
ndk = Path(os.environ['ANDROID_NDK_HOME'])
bin_dir = next((ndk / 'toolchains/llvm/prebuilt').glob('*/bin'))
for arch, target in [('aarch64', 'aarch64-linux-android'), ('armv7', 'armv7a-linux-androideabi'),
                     ('i686', 'i686-linux-android'), ('x86_64', 'x86_64-linux-android')]:
    bindings = (root / f'sys/src/bindings_{arch}.rs').read_text()
    checks = ['#include <oboe/OboeExt.h>']
    for name in ['AudioStreamBase', 'AudioStreamBuilder', 'AudioStream', 'LatencyTuner',
                 'AudioStreamCallbackWrapper']:
        for rust_op, cpp_op in [('size_of', 'sizeof'), ('align_of', 'alignof')]:
            value = re.search(rf'{rust_op}::<oboe_{name}>\(\),\s*(\d+)usize', bindings)[1]
            checks.append(f'static_assert({cpp_op}(oboe::{name}) == {value}, "{arch} {name} {cpp_op}");')
    subprocess.run([str(bin_dir / f'{target}26-clang++'), '-std=c++17', '-fsyntax-only', '-x', 'c++',
                    '-I' + str(root / 'sys/oboe/include'),
                    '-I' + str(root / 'sys/oboe-ext/include'), '-'],
                   input='\n'.join(checks), text=True, check=True)
    print(f'PASS: {arch} Rust storage matches native C++ sizes and alignments')
