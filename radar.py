import math

import matplotlib.pyplot as plt
import serial


PORT = "COM7"
BAUD_RATE = 115200
MAX_DISTANCE_CM = 200


def main():
    try:
        with serial.Serial(PORT, BAUD_RATE, timeout=1) as arduino:
            
            plt.pause(2)

            fig, ax = plt.subplots(subplot_kw={"projection": "polar"})
            ax.set_theta_zero_location("W")
            ax.set_theta_direction(-1)
            ax.set_thetamin(0)
            ax.set_thetamax(180)
            ax.set_ylim(0, MAX_DISTANCE_CM)
            ax.set_rticks([50, 100, 150, 200])
            ax.set_title("Live Arduino Radar")

            beam, = ax.plot([], [], color="lime", linewidth=2)
            dots = ax.scatter([], [], color="red", s=35)
            readings = {}

            print("Radar is running. Close the radar window to stop.")

            while plt.fignum_exists(fig.number):
                line = arduino.readline().decode("utf-8", errors="ignore").strip()
                if not line:
                    plt.pause(0.01)
                    continue

                try:
                    angle_text, distance_text = line.split(",")
                    angle = float(angle_text)
                    distance = float(distance_text)
                except ValueError:
                    continue

                if not 0 <= angle <= 180:
                    continue

                angle_radians = math.radians(angle)
                beam.set_data(
                    [angle_radians, angle_radians],
                    [0, MAX_DISTANCE_CM],
                )

                if 0 < distance <= MAX_DISTANCE_CM:
                    readings[angle_radians] = distance

                if readings:
                    dots.set_offsets(list(readings.items()))

                fig.canvas.draw_idle()
                plt.pause(0.01)

    except serial.SerialException as error:
        print(f"Could not open {PORT}. Check that the Arduino is connected and Serial Monitor is closed.")
        print(error)


if __name__ == "__main__":
    main()
