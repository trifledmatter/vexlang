import serial
import threading


# Function to listen for incoming data from the serial port
def listen_for_response(serial_port, baud_rate):
    with serial.Serial(serial_port, baud_rate, timeout=1) as ser:
        print(f"Listening on {serial_port} at {baud_rate} baud.")
        try:
            while True:
                line = ser.readline().decode("utf-8").strip()
                if line:
                    print(f"Received: {line}")
        except KeyboardInterrupt:
            print("Exiting...")


# Function to send a command over the serial port
def send_command(command, serial_port, baud_rate):
    with serial.Serial(serial_port, baud_rate, timeout=1) as ser:
        ser.write(f"{command}\n".encode("utf-8"))
        print(f"Sent: {command}")


if __name__ == "__main__":
    serial_port = "/dev/ttyACM1"  # Adjust for your system
    baud_rate = 115200  # VEX V5 default baud rate for USB serial

    # Start the listening thread to constantly check for incoming data
    listen_thread = threading.Thread(
        target=listen_for_response, args=(serial_port, baud_rate), daemon=True
    )
    listen_thread.start()

    # Main loop for sending commands
    while True:
        cmd = input("Enter command: ")
        send_command(cmd, serial_port, baud_rate)
