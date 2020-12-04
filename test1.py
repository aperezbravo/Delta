import os

print("hello world")

temp = os.popen('/opt/vc/bin/vcgencmd measure_temp').read();
print(temp)
