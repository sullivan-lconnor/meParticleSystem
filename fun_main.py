import sys
import os

# Add the build directory to sys.path
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, 'src', 'build')
sys.path.insert(0, build_dir)

import random
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
        self.timer.start(16)  # Update every 16 ms or abt 60 frames per second

    def update_simulation(self):
        tics = 0.1
        self.simulator.run(tics)
        self.update()

    def paintEvent(self, event):
        painter = QPainter(self)
        for pos in self.simulator.getPoints():
            mass, x, y = pos
            hue = int((255 * mass) / 10)  # Assuming mass varies from 1 to 10
            color = QColor.fromHsv(hue, 255, 255)  # Fully saturated and bright color based on mass
            painter.setBrush(color)
            painter.drawEllipse(int(x), int(y), mass, mass)  # Draw particles as small circles

class MainWindow(QMainWindow):
    def __init__(self, simulator):
        super().__init__()
        self.simulator = simulator
        self.initUI()

    def initUI(self):
        self.setWindowTitle('Particle Simulation')
        self.setGeometry(0, 0, 1920, 1080)
        widget = ParticleWidget(self.simulator, self)
        self.setCentralWidget(widget)

    def addRandomParticles(self, num_particles):
        mass_range = (1, 10)
        position_range = ((0, 1920), (0, 1080))
        velocity_range = (0, 0)  # No velocity
        acceleration_range = (0, 0)  # No acceleration

        for _ in range(num_particles):
            mass = random.uniform(*mass_range)
            x = random.uniform(*position_range[0])
            y = random.uniform(*position_range[1])
            dx = random.uniform(*velocity_range)
            dy = random.uniform(*velocity_range)
            ddx = random.uniform(*acceleration_range)
            ddy = random.uniform(*acceleration_range)
            self.simulator.addParticle(mass, x, y, dx, dy, ddx, ddy)

if __name__ == '__main__':
    app = QApplication([])

    simulator = simulation.Simulator("test", 2)
    window = MainWindow(simulator)
    window.addRandomParticles(num_particles=500)  # Generate 50 random particles
    window.show()

    app.exec_()
