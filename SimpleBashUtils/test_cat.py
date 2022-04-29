from itertools import combinations_with_replacement
from os import system

my_cat = "./build/mcat"
cat = "cat"

files = [
    'data-samples/t',
    'b.txt',
]

testing_file = 'testing_file'
testing_file_format = ".ntesting"

flags = {
    '-b',
    '-e',
    '-n',
    '-s',
    '-t'}

all_var = list(combinations_with_replacement(flags, len(flags)))

for test in range(len(all_var)):
    cur_flags_ = all_var[test]
    for cur_flags in (cur_flags_, set(cur_flags_)):
        # test with all flags
        print(f"Current test: {test}\t/\t{len(all_var)}")
        for i, func in (('0', my_cat), ('1', cat)):
            m_str = f'{func} {" ".join(cur_flags)} {" ".join(files)} > {testing_file+i+testing_file_format}'
            print("Command:", m_str)
            system(m_str)

        with open(testing_file+'0'+testing_file_format) as file_1:
            with open(testing_file+'1'+testing_file_format) as file_2:
                a, b = file_1.read(), file_2.read()
                if a != b:
                    print("\n\nТУТ ЕСТЬ ОШИБКА ХОЗЯИН ОЗНАКОМТЕСЬ!!!\n\n")
                    print("===============A===============")
                    print(a[-100:])
                    print("===============B===============")
                    print(b[-100:])
                    print("===============================")
                    input("Нажмите для продолжения...\n")
                    print("Продолжаем!\n\n")
        print()
