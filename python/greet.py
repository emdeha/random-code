from urllib import urlretrieve
import imp
import fbconsole
import time
from datetime import date, timedelta

urlretrieve('https://raw.github.com/facebook/fbconsole/master/src/fbconsole.py', 'fbconsole.py')
fb = imp.load_source('fb', 'fbconsole.py')
fb.AUTH_SCOPE = ['publish_stream', 'publish_checkins', 'friends_birthday']
fb.authenticate()

today = date.today()
nextDay = today + timedelta(1)
query = ("SELECT username FROM user WHERE uid IN "
	     "(SELECT uid2 FROM friend WHERE uid1 = me()) AND "
	     "(substr(birthday_date, 0, 2) = \'" + today.strftime("%m") + "\' AND "
	     "substr(birthday_date, 3, 5) >= \'" + today.strftime("%d") + "\' AND "
	     "substr(birthday_date, 3, 5) <= \'" + nextDay.strftime("%d") + "\')")
names = fb.fql(query)

print "Birthdays greeted: "
if names == []:
    print "None"
else:
    message = "Chestit rojden den! :)"
    for name in names:
        path = "/" + name.get('username') + "/feed"
        fb.graph_post(path, {'message':message})
        print name.get('username')
