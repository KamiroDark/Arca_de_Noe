import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Configura el puerto serial (ajusta 'COM5' según tu sistema)
arduino = serial.Serial('COM3', 9600, timeout=1)

tiempo = []
profundidad = []

fig, ax = plt.subplots()
linea, = ax.plot([], [], lw=2)

def init():
    ax.set_xlim(0, 100)
    ax.set_ylim(0, 100)
    return linea,

def actualizar(frame):
    if arduino.in_waiting > 0:
        try:
            datos = arduino.readline().decode('utf-8').strip()
            if datos:
                profundidad_actual = float(datos)
                tiempo.append(len(tiempo))
                profundidad.append(profundidad_actual)

                if len(tiempo) > 100:
                    tiempo.pop(0)
                    profundidad.pop(0)

                linea.set_data(tiempo, profundidad)
                ax.set_xlim(0, max(100, len(tiempo)))
                if profundidad:
                    ax.set_ylim(0, max(100, max(profundidad) + 10))
        except Exception as e:
            print(f"Error al leer datos del puerto serial: {e}")

    return linea,

ani = animation.FuncAnimation(fig, actualizar, init_func=init, blit=False, interval=500)

plt.xlabel('Tiempo (s)')
plt.ylabel('Profundidad (cm)')
plt.title('Profundidad del agua en el tanque en tiempo real')

try:
    plt.show()
finally:
    arduino.close()
    print("Conexión serial cerrada.")
