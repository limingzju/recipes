import commands
import sys
from oss.oss_api import *
from oss_config import *


oss = OssAPI("oss.aliyuncs.com", ACCESS_KEY_ID, ACCESS_KEY_PASSWD)
if len(sys.argv) == 1:
  if sys.platform == 'linux2':
    res = oss.get_object_to_file('xiaoheshang', 'darwin', '/tmp/remote.txt') 
    assert(res.status == 200)
    print(open('/tmp/remote.txt').read())
  elif sys.platform == 'darwin':
    res = oss.get_object_to_file('xiaoheshang', 'linux2', '/tmp/remote.txt')
    assert(res.status == 200)
    print(open('/tmp/remote.txt').read())
  else:
    sys.exit(1)
elif len(sys.argv) == 2:
  res = oss.get_object_to_file('xiaoheshang', sys.argv[1], '/tmp/remote.txt') 
  assert(res.status == 200)
  print(open('/tmp/remote.txt').read())
else:
  print('Error')  

