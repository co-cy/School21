from src.frontend.calc import Ui_MainWindow
from src.backend.translator import Backend
from pyqtgraph import PlotWidget, mkPen
from PyQt6 import QtWidgets, QtCore


class CalcMainWindows(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.__init2__()

        self.is_result = 0

    def __init2__(self):
        self.view = view = PlotWidget()
        self.view.showGrid(x=True, y=True)
        self.graph_pen = mkPen(color=(0, 255, 0), width=15, style=QtCore.Qt.PenStyle.NoPen)
        self.curve = view.plot(name="Graph", pen=self.graph_pen,  symbol='o', symbolSize=8)

        self.graph_verticalLayout.insertWidget(0, view)

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
        old_text = self.expression.text()
        if self.is_result:
            old_text = old_text.split(" =")[0].strip()
        self.is_result = 1

        if 'x' in old_text.split():
            list_x = []
            list_y = []
            step_x = self.step_x.value()
            x = self.min_x.value()
            while x <= self.max_x.value():
                x += step_x

                list_x.append(x)
                res = Backend.calc_exp(old_text, x=x)
                if not isinstance(res, float):
                    text = str(Backend.calc_exp(old_text))
                    break

                list_y.append(res)
            else:
                text = "График построен"
                self.curve.setData(list_x, list_y)

                self.tabWidget.setCurrentWidget(self.graph_grid)
        else:
            text = str(Backend.calc_exp(old_text))

        self.expression.setText(f" {old_text} = {text}")

    def change_tab_bar(self, index: int):
        if self.tabWidget.widget(index).objectName() == self.graph_grid.objectName():
            pass
