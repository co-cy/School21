from random import randrange, choice, shuffle
from itertools import combinations
from os import system

stop = 1
more = 1

s21_grep = "./build/s21_grep"
grep = "grep"

tmp_file = '0_{}.res'
s21_grep_file = tmp_file.format(s21_grep.split('/')[-1])
grep_file = tmp_file.format(grep)
diff_file = tmp_file.format('diff')

flags = [
    ('-e', 1),
    ('-i', 0),
    ('-v', 0),
    ('-c', 0),
    ('-l', 0),
    ('-n', 0),
    ('-h', 0),
    ('-s', 0),
    ('-f', 2),
    ('-o', 0),
]

files = [
    'data-samples/grep_file1',
    'data-samples/grep_file2',
    'data-samples/grep_file3',
    'data-samples/grep_file4',
]

patterns = [
    'permission',
    'Permission',
    'is',
    'modify',
    'Back-Cover',
    '.Texts',
] + files


#
#        START PROGRAM
#

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


flags += flags

TEST_COUNT = 0
TEST_COUNT_FAILED = 0


def get_argv(flag: str, type: int) -> str:
    if type == 2:
        flag += f'{(" " if randrange(0, 1) else "")}{choice(files)}'
    if type == 1:
        flag += f'{(" " if randrange(0, 1) else "")}{choice(patterns)}'

    return flag


def run_test(command_1: str, command_2: str) -> None:
    global TEST_COUNT, TEST_COUNT_FAILED

    TEST_COUNT += 1

    system(command_1)
    system(command_2)

    if system(f'diff {s21_grep_file} {grep_file} > {diff_file}'):
        print()
        print(f'{bcolors.BOLD}{bcolors.OKCYAN}{"TEST "}{bcolors.ENDC}{bcolors.OKGREEN}{TEST_COUNT}{bcolors.ENDC}{": "}{bcolors.ENDC}{bcolors.FAIL}{"FAILED"}{bcolors.ENDC}')

        if more:
            print()
            print(f'{bcolors.WARNING}{bcolors.BOLD}{"ARGUMENT:"}{bcolors.ENDC}{bcolors.ENDC}')
            print(command_1[len(s21_grep) + 1:-2])
            print()
            print(f'{bcolors.WARNING}{bcolors.BOLD}{"FLAGS:"}{bcolors.ENDC}{bcolors.ENDC}')
            for flag in filter(lambda x: x[0] == '-', command_1[len(s21_grep) + 1:].split()[:-2]):
                print(flag)
            print()
            print(f'{bcolors.WARNING}{bcolors.BOLD}{"FILES:"}{bcolors.ENDC}{bcolors.ENDC}')
            for file in filter(lambda x: x[0] != '-', command_1[len(s21_grep) + 1:].split()[:-2]):
                print(file)
        print()
        print(f'{bcolors.FAIL}{bcolors.BOLD}{"COMMANDS:"}{bcolors.ENDC}{bcolors.ENDC}')
        print(command_1)
        print(command_2)
        print()
        print(f'{bcolors.FAIL}DIFF IN:{bcolors.ENDC}')
        print(diff_file)
        print()
        if stop:
            input()
        TEST_COUNT_FAILED += 1
    else:
        print(f'{bcolors.BOLD}{bcolors.OKBLUE}TEST{bcolors.ENDC} {bcolors.OKGREEN}{TEST_COUNT}{bcolors.ENDC}: {bcolors.OKGREEN}{"SUCCESS"}{bcolors.ENDC}{bcolors.ENDC}')
        print()


def simple_test():
    for flag, type in flags:
        argv = [get_argv(flag, type)]

        for _ in range(randrange(1, len(files))):
            argv.append(choice(files))

        shuffle(argv)
        if not type:
            argv.insert(0, choice(patterns))
        argv = ' '.join(argv)

        run_test(f'{s21_grep} {argv} > {s21_grep_file}',
                 f'{grep} {argv} > {grep_file}')


def hard_test():
    # count = 0
    for i in range(1, len(flags)):
        # count += len(list(combinations(flags, i)))
        for list_arg in combinations(flags, i):
            list_arg = list(list_arg)
            shuffle(list_arg)

            was_pattern = 0
            argv = []
            for arg_flag, arg_type in list_arg:
                was_pattern += arg_type
                argv.append(get_argv(arg_flag, arg_type))

            for _ in range(randrange(1, len(files))):
                argv.append(choice(files))

            shuffle(argv)
            if not was_pattern:
                argv.insert(0, choice(patterns))
            argv = ' '.join(argv)

            run_test(f'{s21_grep} {argv} > {s21_grep_file}',
                     f'{grep} {argv} > {grep_file}')
    # print(count)


if __name__ == '__main__':
    simple_test()
    hard_test()

    print("WAS TEST:\t", TEST_COUNT)
    print("SUCC:\t", TEST_COUNT - TEST_COUNT_FAILED)
    print("FAILED:\t", TEST_COUNT_FAILED)
