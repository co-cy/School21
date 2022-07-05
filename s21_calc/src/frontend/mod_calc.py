from src.frontend.calc import Ui_MainWindow
from src.backend.translator import Backend
from PyQt6 import QtWidgets


class CalcMainWindows(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

        self.is_result = 0

        self.number_0.clicked.connect(lambda _: self.add_text_to_expression("0"))
        self.number_1.clicked.connect(lambda _: self.add_text_to_expression("1"))
        self.number_2.clicked.connect(lambda _: self.add_text_to_expression("2"))
        self.number_3.clicked.connect(lambda _: self.add_text_to_expression("3"))
        self.number_4.clicked.connect(lambda _: self.add_text_to_expression("4"))
        self.number_5.clicked.connect(lambda _: self.add_text_to_expression("5"))
        self.number_6.clicked.connect(lambda _: self.add_text_to_expression("6"))
        self.number_7.clicked.connect(lambda _: self.add_text_to_expression("7"))
        self.number_8.clicked.connect(lambda _: self.add_text_to_expression("8"))
        self.number_9.clicked.connect(lambda _: self.add_text_to_expression("9"))
        self.number_x.clicked.connect(lambda _: self.add_text_to_expression("x"))

        self.point.clicked.connect(lambda _: self.add_text_to_expression("."))
        # self.negate.clicked.connect(self.negate_last_word)

        self.calc_exp.clicked.connect(self.calc)

        self.sum.clicked.connect(lambda _: self.add_text_to_expression("+"))
        self.sub.clicked.connect(lambda _: self.add_text_to_expression("-"))
        self.div.clicked.connect(lambda _: self.add_text_to_expression("/"))
        self.mul.clicked.connect(lambda _: self.add_text_to_expression("*"))
        self.mod.clicked.connect(lambda _: self.add_text_to_expression("mod"))

        self.clear.clicked.connect(self.clear_expression)
        self.cancel.clicked.connect(self.cancel_expression)

        self.exponent.clicked.connect(lambda _: self.add_text_to_expression("e"))

        self.open_bracket.clicked.connect(lambda _: self.add_text_to_expression("("))
        self.close_bracket.clicked.connect(lambda _: self.add_text_to_expression(")"))

        self.cos.clicked.connect(lambda _: self.add_text_to_expression("cos ("))
        self.acos.clicked.connect(lambda _: self.add_text_to_expression("acos ("))
        self.sin.clicked.connect(lambda _: self.add_text_to_expression("sin ("))
        self.asin.clicked.connect(lambda _: self.add_text_to_expression("asin ("))
        self.tan.clicked.connect(lambda _: self.add_text_to_expression("tan ("))
        self.atan.clicked.connect(lambda _: self.add_text_to_expression("atan ("))
        self.sqrt.clicked.connect(lambda _: self.add_text_to_expression("sqrt ("))
        self.pow.clicked.connect(lambda _: self.add_text_to_expression("^"))
        self.log.clicked.connect(lambda _: self.add_text_to_expression("log ("))
        self.nat_log.clicked.connect(lambda _: self.add_text_to_expression("ln ("))

    def add_text_to_expression(self, text):
        if self.is_result:
            self.is_result = 0
            cur_exp = ""
        else:
            cur_exp = self.expression.text()
        last_symbol = cur_exp[-1] if cur_exp else ""

        if not last_symbol or ((last_symbol.isalnum() or last_symbol == '.') and (text.isalnum() or text == '.')):
            cur_exp += text
        else:
            cur_exp = f'{cur_exp} {text}'

        self.expression.setText(cur_exp)

    def clear_expression(self):
        self.expression.setText("")

    def cancel_expression(self):
        self.expression.setText(self.expression.text()[:-1])

    # def negate_last_word(self):
    #     cur_text = self.expression.text()
    #     find_pos = cur_text.find(" ")
    #     if find_pos != -1:
    #         if cur_text[find_pos + 1] == '-':
    #             self.expression.setText(f"{cur_text[:find_pos]}{cur_text[find_pos + 2:]}")

    def calc(self):
        self.is_result = 1
        self.expression.setText(f"= {Backend.calc_exp(self.expression.text())}")
