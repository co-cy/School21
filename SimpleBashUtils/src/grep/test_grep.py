from termios import tcgetattr, tcsetattr, TCSADRAIN
from itertools import combinations_with_replacement
from random import randrange, choice, shuffle
from tty import setcbreak
from select import select
from time import sleep
from sys import stdin
from os import system


# 1 или 0 останавливать тесты после ошибки или нет
stop = 1
# 1 или 0 показывать расшириный вывод ошибки
more = 1
# 1 или 0 если показывать в конце список комманд
show_log = 0
# любый символы остановки вывода
quit_command = ['q', 'z']

# Указать пути до грепов
s21_grep = "./s21_grep"
grep = "grep"

# Путь где будут распологаться результаты
tmp_file = '0_{}.res'


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
    '../../data-samples/grep_file1',
    '../../data-samples/grep_file2',
    '../../data-samples/grep_file3',
    '../../data-samples/grep_file4',
    '../../data-samples/a',
    '../../data-samples/c',
    '../../data-samples/new',
    '../../data-samples/v2',
    '../../data-samples/void',
    '../../data-samples/pat',
    '../../data-samples/char',
    '../../data-samples/text',
]

files_with_patterns = [] + files

patterns = [
               'permission',
               'Permission',
               'is',
               'void',
               'voiD',
               'aboba',
               'abob',
               'boba',
               'Lorem',
               'modify',
               'Back-Cover',
               '.Texts',
               # '.',
           ] + files


#
#        START PROGRAM
#

test_error = []

TEST_COUNT = 0
TEST_COUNT_FAILED = 0

s21_grep_file = tmp_file.format(s21_grep.split('/')[-1])
grep_file = tmp_file.format(grep)
diff_file = tmp_file.format('diff')

_files = []
_flags = []


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


def is_data():
    return select([stdin], [], [], 0) == ([stdin], [], [])


def get_argv(flag: str, type: int) -> str:
    if type == 2:
        flag += f'{(" " if randrange(0, 2) else "")}{choice(files_with_patterns)}'
    if type == 1:
        flag += f'{(" " if randrange(0, 2) else "")}{choice(patterns)}'

    return flag


def get_persent() -> str:
    res = f'{bcolors.BOLD}\t{bcolors.OKBLUE}{TEST_COUNT}{bcolors.ENDC}\t/\t{bcolors.OKGREEN}{TEST_COUNT - TEST_COUNT_FAILED}{bcolors.ENDC}\t/\t{bcolors.FAIL}{TEST_COUNT_FAILED}{bcolors.ENDC}{bcolors.ENDC}\n'
    if TEST_COUNT_FAILED:
        persent = ((TEST_COUNT - TEST_COUNT_FAILED) / TEST_COUNT) * 100
    else:
        persent = 100

    if persent > 80:
        res += f'{bcolors.BOLD}{bcolors.WARNING}PERCENT: \t{bcolors.ENDC}{bcolors.OKGREEN}{persent}%{bcolors.ENDC}{bcolors.ENDC}{bcolors.ENDC}'
    elif persent > 50:
        res += f'{bcolors.BOLD}{bcolors.WARNING}PERCENT: \t{bcolors.ENDC}{bcolors.WARNING}{persent}%{bcolors.ENDC}{bcolors.ENDC}{bcolors.ENDC}'
    else:
        res += f'{bcolors.BOLD}{bcolors.WARNING}PERCENT: \t{bcolors.ENDC}{bcolors.FAIL}{persent}%{bcolors.ENDC}{bcolors.ENDC}{bcolors.ENDC}'
    return res


def run_test(command_1: str, command_2: str) -> int:

    # system(f"valgrind --leak-check=full \
    #      --show-leak-kinds=all \
    #      --track-origins=yes \
    #      --verbose \
    #      --log-file=valgrind-out \
    #     {command_1}; grep -e 'ERROR SUMMARY' valgrind-out | grep -e 'ERROR SUMMARY: 0' -v")
    # print(command_1)
    # print()
    #
    # return
    global TEST_COUNT, TEST_COUNT_FAILED, _flags, _files

    TEST_COUNT += 1

    a = system(command_1)
    b = system(command_2)
    if b == 256:
        b = 0
    if a:
        TEST_COUNT_FAILED += 1
    diff_command = f'diff {s21_grep_file} {grep_file} > {diff_file}'

    if a == b and system(diff_command):
        if show_log:
            test_error.append((command_1, command_2))
        print()
        print(f'{bcolors.BOLD}{bcolors.OKCYAN}{"TEST "}{bcolors.ENDC}{bcolors.OKGREEN}{TEST_COUNT}{bcolors.ENDC}{": "}{bcolors.ENDC}{bcolors.FAIL}{"FAILED"}{bcolors.ENDC}')

        if more:
            print()
            print(f'{bcolors.WARNING}{bcolors.BOLD}{"ARGUMENT:"}{bcolors.ENDC}{bcolors.ENDC}')
            print(command_1[len(s21_grep) + 1:-2])
            print()
            print(f'{bcolors.WARNING}{bcolors.BOLD}{"FLAGS:"}{bcolors.ENDC}{bcolors.ENDC}')
            for flag in _flags:
                print(flag)
            print()
            print(f'{bcolors.WARNING}{bcolors.BOLD}{"FILES:"}{bcolors.ENDC}{bcolors.ENDC}')
            for file in _files:
                print(file)
            print()
        print(f'{bcolors.FAIL}{bcolors.BOLD}{"COMMANDS:"}{bcolors.ENDC}{bcolors.ENDC}')
        print(command_1)
        print(command_2)
        print(diff_command)
        print()
        print(f'{bcolors.FAIL}DIFF IN:{bcolors.ENDC}')
        system(diff_command)
        print(diff_file)
        print()
        if stop and input() in quit_command:
            return -1
        TEST_COUNT_FAILED += 1
    elif a != b:
        print(f"{bcolors.BOLD}{bcolors.OKBLUE}\t\tCRASH\t\t{bcolors.ENDC}{bcolors.ENDC}")
        print(command_1)
        print(command_2)
        print(diff_command)
        print(f'\ns21_grep={a}\t'
              f'grep={b}\n')
        print('\t\tWAIT 3 SEC\t\t')
        # sleep(3)
    else:
        print(get_persent())
        print(f'{bcolors.BOLD}{bcolors.OKBLUE}TEST{bcolors.ENDC} {bcolors.OKGREEN}{TEST_COUNT}{bcolors.ENDC}: {bcolors.OKGREEN}{"SUCCESS"}{bcolors.ENDC}{bcolors.ENDC}')
        print()

    _flags = []
    _files = []

    system(f"rm -f {grep_file}")
    system(f"rm -f {s21_grep_file}")
    system(f"rm -f {tmp_file}")


def simple_test():
    for flag, type in flags:
        f = get_argv(flag, type)
        _flags.append(f)
        argv = [f]

        for _ in range(randrange(1, len(files))):
            g = choice(files)
            argv.append(g)
            _files.append(g)

        shuffle(argv)
        if not type:
            g = choice(patterns)
            argv.insert(0, g)
            _flags.append(f'-e {g}')
        argv = ' '.join(argv)

        run_test(f'{s21_grep} {argv} > {s21_grep_file}',
                 f'{grep} --color=never {argv} > {grep_file}')


def hard_test():
    global _flags, _files
    # count = 0
    for i in range(round(len(flags) / 2), len(flags)):
        for list_arg_m in combinations_with_replacement(flags, i):
            for list_arg in (set(list_arg_m), list_arg_m):
                list_arg = list(list_arg)
                shuffle(list_arg)

                _flags = []
                _files = []

                was_pattern = 0
                argv = []
                for arg_flag, arg_type in list_arg:
                    was_pattern += arg_type
                    _flags.append(get_argv(arg_flag, arg_type))
                argv += _flags

                for _ in range(randrange(1, len(files))):
                    _files.append(choice(files))
                argv += _files

                shuffle(argv)
                if not was_pattern:
                    argv.insert(0, choice(patterns))
                argv = ' '.join(argv)

                res = run_test(f'{s21_grep} {argv} > {s21_grep_file}', f'{grep} --color=never {argv} > {grep_file}')
                if res == -1:
                    return
                if is_data():
                    c = stdin.read(1)

                    if c in quit_command:
                        return

# print(count)


if __name__ == '__main__':
    old_settings = tcgetattr(stdin)

    try:
        setcbreak(stdin.fileno())

        print("\t\tEASY TEST:")
        for _ in range(10):
            simple_test()

        print("\n\t\tHARD TEST:\n\n")
        sleep(0.25)
        hard_test()

        print(f'{bcolors.BOLD}{bcolors.OKCYAN}WAS TEST: \t{bcolors.ENDC}{bcolors.OKBLUE}{TEST_COUNT}{bcolors.ENDC}{bcolors.ENDC}{bcolors.ENDC}')
        print(f'{bcolors.BOLD}{bcolors.OKBLUE}SUCCESS: \t{bcolors.ENDC}{bcolors.OKGREEN}{TEST_COUNT - TEST_COUNT_FAILED}{bcolors.ENDC}{bcolors.ENDC}{bcolors.ENDC}')
        print(f'{bcolors.BOLD}{bcolors.WARNING}FAILED: \t{bcolors.ENDC}{bcolors.FAIL}{TEST_COUNT_FAILED}{bcolors.ENDC}{bcolors.ENDC}{bcolors.ENDC}')

        print(get_persent())

        if more:
            print("\n\n\t\tALL ERRORS\t\t\n\n")
            for i in range(len(test_error)):
                run_test(*test_error[i])
    finally:
        tcsetattr(stdin, TCSADRAIN, old_settings)