from src.frontend.mod_calc import CalcMainWindows
from PyQt6.QtWidgets import QApplication


app = QApplication([])
wd = CalcMainWindows()
wd.show()

app.exec()