import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

try:
    # Intentar abrir el puerto serial
    arduino = serial.Serial('COM4', 115200, timeout=1)  
except serial.SerialException as e:
    print(f"Error al conectar con el puerto serial: {e}")
    arduino = None

if arduino:
    tiempo = []
    profundidad = []

    fig, ax = plt.subplots()
    linea, = ax.plot([], [], lw=2)

    def init():
        ax.set_xlim(0, 100)  # Puedes ajustar esto dinámicamente si lo prefieres
        ax.set_ylim(0, 100)
        return linea,

    def actualizar(frame):
        global tiempo, profundidad

        if arduino.in_waiting > 0:
            try:
                datos = arduino.readline().decode('utf-8').strip()
                profundidad_actual = float(datos)  # Intentar convertir a float
                tiempo.append(len(tiempo))
                profundidad.append(profundidad_actual)

                # Limitar los datos a los últimos 100 puntos
                if len(tiempo) > 100:
                    tiempo.pop(0)
                    profundidad.pop(0)

                # Actualizar los datos de la gráfica
                linea.set_data(tiempo, profundidad)

                # Ajustar límites dinámicamente si es necesario
                ax.set_xlim(0, max(100, len(tiempo)))
                ax.set_ylim(0, max(100, max(profundidad) + 10))
            except ValueError:
                print("Dato recibido no válido, ignorado.")

        return linea,

    ani = animation.FuncAnimation(fig, actualizar, init_func=init, blit=True, interval=1000)

    plt.xlabel('Tiempo (s)')
    plt.ylabel('Profundidad (cm)')
    plt.title('Profundidad del agua en el tanque en tiempo real')

    try:
        plt.show()
    finally:
        # Asegurarse de cerrar el puerto serial
        arduino.close()
        print("Conexión serial cerrada.")