from ctypes import CDLL, pointer, c_longdouble, c_char_p


class Backend:
    c_library = CDLL("src/backend/backend.so")

    @classmethod
    def calc_exp(cls, string: str) -> float | str:
        double_res = c_longdouble(0)

        status = cls.c_library.calc(c_char_p(string.encode('utf-8')), pointer(double_res))

        if status:
            result = "Ошибка вычисления"
        else:
            result = double_res.value

        return result

