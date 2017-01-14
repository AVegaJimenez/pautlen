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
	args = parser.parse_args()
	return args

def main(args):
	if args.input:
		stdin = open(args.input, 'r')
	else:
		stdin = None

	if args.output:
		stdout = open(args.output, 'br')
	else:
		stdout = None

	with subprocess.Popen([args.action], stdin=stdin, stdout=subprocess.PIPE) as proc:
		exp_output_b = stdout.read()
		exp_output_b = exp_output_b.replace(b'\n\n', b'\n')
		exp_output_b = exp_output_b.replace(b'\r\n', b'\n')
		exp_output = str(exp_output_b)

		output_b = proc.stdout.read()
		output = str(output_b)

		res = output == exp_output
		if res == True:
			print(bcolors.GREEN + "Test " + bcolors.CYAN + args.action + bcolors.GREEN + " successfully passed." + bcolors.RESET)
		else:
			print(bcolors.RED + "Expected output")
			print(exp_output_b.decode())
			print(exp_output)
			print(bcolors.YELLOW + "Program output")
			print(output_b.decode())
			print(output)
			print(bcolors.RED + "Test " + bcolors.CYAN + args.action + bcolors.RED + " failed." + bcolors.RESET)


if __name__ == '__main__':
	args = parse_args()
	main(args)

