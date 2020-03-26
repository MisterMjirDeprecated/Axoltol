import axoltol
import time

class Test:
    def window():
        axoltol.init()
        window = axoltol.Window()
        time.sleep(1)
        axoltol.quit()

if __name__ == "__main__":
    Test.window()
    print("Everything successful!")
