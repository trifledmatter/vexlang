import serial
import threading
import re


class SerialCommunication:
    def __init__(self, serial_port, baud_rate):
        self.serial_port = serial_port
        self.baud_rate = baud_rate
        self.stop_listening = False
        self.message_pattern = re.compile(r"<#>(.*?)<#>")
        self.serial_connection = serial.Serial(
            self.serial_port, self.baud_rate, timeout=5
        )

    def listen_for_response(self):
        print(f"Listening on {self.serial_port} at {self.baud_rate} baud.\n")
        try:
            while not self.stop_listening:
                try:
                    line = self.serial_connection.readline().decode("utf-8").strip()
                    match = self.message_pattern.search(line)
                    if match:
                        message = match.group(1)
                        print(f"\n< {message}")
                except serial.SerialException as e:
                    print(f"\nSerial error: {e}")
        except KeyboardInterrupt:
            print("\nExiting listener...")
        finally:
            self.stop()

    def send_command(self, command):
        try:
            formatted_command = f"{command}\n"
            self.serial_connection.write(formatted_command.encode("utf-8"))
            self.serial_connection.flush()  # Ensure data is sent immediately
            print(f"\n> {command}")
        except serial.SerialException as e:
            print(f"\nSerial error while sending command: {e}")

    def stop(self):
        self.stop_listening = True
        if self.serial_connection and self.serial_connection.is_open:
            self.serial_connection.close()
        print("\nSerial communication stopped.")


if __name__ == "__main__":
    serial_port = "/dev/ttyACM1"  # Adjust for your system
    baud_rate = 115200  # VEX V5 default baud rate for USB serial

    serial_comm = SerialCommunication(serial_port, baud_rate)

    # Start the listening thread to constantly check for incoming data
    listen_thread = threading.Thread(
        target=serial_comm.listen_for_response, daemon=True
    )
    listen_thread.start()

    try:
        while True:
            cmd = input("Enter command: ").strip()
            if cmd.lower() in ["exit", "quit"]:
                print("Exiting...")
                serial_comm.stop()
                break
            if cmd:
                serial_comm.send_command(cmd)
    except KeyboardInterrupt:
        print("\nKeyboardInterrupt detected. Exiting...")
        serial_comm.stop()
    finally:
        listen_thread.join()
