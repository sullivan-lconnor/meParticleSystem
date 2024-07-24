import sys
import os

# Add the build directory to sys.path
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, 'src', 'build')
sys.path.insert(0, build_dir)

from PySide2.QtWidgets import QApplication, QMainWindow, QWidget, QVBoxLayout
from PySide2.QtGui import QPainter, QColor
from PySide2.QtCore import QTimer
import simulation

class ParticleWidget(QWidget):
    def __init__(self, simulator, parent=None):
        super().__init__(parent)
        self.simulator = simulator
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.update_simulation)
        self.timer.start(1)  # Update every 100 ms

    def update_simulation(self):
        tics = 0.01
        self.simulator.run(tics)
        self.update()

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setBrush(QColor(255, 0, 0))
        for pos in self.simulator.getPoints():
            x, y = pos
            print(pos)
            painter.drawEllipse(int(x), int(y), 5, 5)
        

class MainWindow(QMainWindow):
    def __init__(self, simulator):
        super().__init__()
        self.simulator = simulator
        self.initUI()

    def initUI(self):
        self.setWindowTitle('Particle Simulation')
        self.setGeometry(100, 100, 800, 600)
        widget = ParticleWidget(self.simulator, self)
        self.setCentralWidget(widget)

if __name__ == '__main__':
    app = QApplication([])

    simulator = simulation.Simulator("test", 2)
    simulator.addParticle(1, 260, 250, 0, 0, 0, 0)
    simulator.addParticle(1, 275, 250, 0, 0, 0, 0)
    window = MainWindow(simulator)
    window.show()

    app.exec_()
