import sys
import os
import subprocess
import json
import traceback

def run_test(source, expected):
    try:
        res = subprocess.run(
            ["./plsc", "--dump-token", source], capture_output=True)
        if res.returncode != 0:
            return False
        clean_out = res.stdout.replace(b'\\', b'/')
        with open(expected, "r") as f:
            expected_obj = json.load(f)
        return expected_obj == json.loads(clean_out)
    except Exception as err:
        print(err)
        return False

if __name__ == '__main__':
    error = 0
    for path in os.listdir(sys.argv[1]):
        if path.endswith('.input'):
            path = os.path.join(sys.argv[1], path)
            if run_test(path, path.replace('.input', '.expected')):
                print(f"[+] {path}: success")
            else:
                print(f"[-] {path}: failed")
                error += 1
    sys.exit(error)
