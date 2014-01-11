import commands
import sys
from oss.oss_api import *
from oss_config import *

oss = OssAPI("oss.aliyuncs.com", ACCESS_KEY_ID, ACCESS_KEY_PASSWD)

# get ip addres
(s, o) = commands.getstatusoutput("/sbin/ifconfig |grep 'inet addr'|grep -v '127.0.0.1'|awk '{print $2}'|tr -d 'addr:'")
o = o.strip()
assert len(o) > 0


res = oss.put_object_from_string('xiaoheshang', sys.platform, o , 'plain/text')
assert res.status == 200

res = oss.get_object_to_file('xiaoheshang', sys.platform, '/tmp/myhost.txt')

host = open('/tmp/myhost.txt').read()
assert host==o

