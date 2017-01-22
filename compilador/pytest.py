import subprocess
import argparse

class bcolors:
	RED = "\033[91m"
	GREEN = "\033[92m"
	YELLOW = "\033[93m"
	LIGHTPURPLE = "\033[94m"
	PURPLE = "\033[95m"
	CYAN = "\033[96m"
	LIGHTGRAY = "\033[97m"
	BLACK = "\033[98m"
	RESET = "\033[00m"

def parse_args():
	parser = argparse.ArgumentParser(description='Simple test environment')
	parser.add_argument('action', help='Command to be performed')
	parser.add_argument('--input', help='Input file')
	parser.add_argument('--output', help='Output file')
	parser.add_argument('--stderr', help='Error output file')
	parser.add_argument('--args', help='arguments', nargs='*')
	args = parser.parse_args()
	return args

def main(args):
	if args.input:
		stdin = open(args.input, 'r')
	else:
		stdin = None

	if args.output:
		stdout = open(args.output, 'rb')
	else:
		stdout = None

	if args.stderr:
		stderr = open(args.output, 'rb')
	else:
		stderr = None

	exe = [args.action]
	if args.args:
		exe = exe + args.args
	proc = subprocess.Popen(exe, stdin=stdin, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

	# Processing expected output
	if stdout == None:
		exp_output_b = b''
		exp_output = ''
	else: 
		exp_output_b = stdout.read()
		exp_output_b = exp_output_b.replace(b'\n\n', b'\n')
		exp_output_b = exp_output_b.replace(b'\r\n', b'\n')
		exp_output = str(exp_output_b)


	output_b = proc.stdout.read()
	output = str(output_b)
	res = output_b == exp_output_b

	if res == False:
		print(bcolors.RED + "Expected output")
		print(exp_output_b.decode())
		print(exp_output)
		print(bcolors.YELLOW + "Program output")
		print(output_b.decode())
		print(output)


	if stderr == None:
		exp_stderr_b = b''
		exp_stderr = ''
	else: 
		print ('err')
		exp_stderr_b = stderr.read()
		exp_stderr_b = exp_stderr_b.replace(b'\n\n', b'\n')
		exp_stderr_b = exp_stderr_b.replace(b'\r\n', b'\n')
		exp_stderr = str(exp_stderr_b)


	stderr_b = proc.stderr.read()
	stderr_out = str(stderr_b)
	res2 = (stderr_b == exp_stderr_b)

	if res2 == False:
		print(bcolors.RED + "Expected (stderr) output")
		print(exp_stderr_b.decode())
		print(exp_stderr)
		print(bcolors.YELLOW + "Program (stderr) output")
		print(stderr_b.decode())
		print(exp_stderr)

	name = '%s (in=%s, out=%s, err=%s)' % (args.action, args.input, args.output, args.stderr)
	if res == False or res2 == False:
		print(bcolors.RED + "Test " + bcolors.CYAN + name + bcolors.RED + " failed." + bcolors.RESET)
	else:
		print(bcolors.GREEN + "Test " + bcolors.CYAN + name + bcolors.GREEN + " successfully passed." + bcolors.RESET)


if __name__ == '__main__':
	args = parse_args()
	main(args)

