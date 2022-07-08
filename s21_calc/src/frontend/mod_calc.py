from src.frontend.calc import Ui_MainWindow
from src.backend.translator import Backend
from pyqtgraph import PlotWidget
from PyQt6 import QtWidgets


class CalcMainWindows(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.__init2__()

        self.is_result = 0

    def __init2__(self):
        self.view = view = PlotWidget()
        self.curve = view.plot(name="Graph")

        self.graph_verticalLayout.addWidget(view)

        self.tabWidget.tabBarClicked.connect(self.change_tab_bar)

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

        if (not last_symbol) or (
                (last_symbol.isdigit() or last_symbol == '.') and (text.isdigit() or text == '.')):
            cur_exp += text
        else:
            cur_exp = f'{cur_exp} {text}'

        self.expression.setText(cur_exp)

    def clear_expression(self):
        self.expression.setText("")

    def cancel_expression(self):
        if self.is_result:
            self.clear_expression()
        else:
            cur_text = self.expression.text()
            i = len(cur_text) - 1
            for i in range(i, -1, -1):
                if cur_text[i] == " ":
                    break
            self.expression.setText(cur_text[:i])

    def calc(self):
        self.is_result = 1
        old_text = self.expression.text()
        self.expression.setText(f"= {Backend.calc_exp(old_text)}")

        if 'x' in old_text.split():
            self.tabWidget.setCurrentWidget(self.graph_grid)

    def change_tab_bar(self, index: int):
        if self.tabWidget.widget(index).objectName() == self.graph_grid.objectName():
            hour = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
            temperature = [30, 32, 34, 32, 33, 31, 29, 32, 35, 45]
            self.curve.setData(hour, temperature)
