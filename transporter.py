#!/usr/bin/python
import cgi, csv, cgitb
cgitb.enable()

print "Content-type:text/html"
print ""

# Receive two parameters
form = cgi.FieldStorage()
# 1) Player's inventory
inventory = form.getvalue('inventory')	# NOT CHECKING IF THE TRANSPORTER PLAYER HAS 0 MANNA ATM, BUT MIGHT NEED TO
# 2) URL of the room the player came from (to the a.out/room.cgi file)
URL = form.getvalue('URL')
# and an additional parameter for the link to the resources file of the other room
source_room_success = form.getvalue('successURL')

# TEST
#inventory = '10,10'
#URL = 'http://www.cs.mcgill.ca/~syu47/cgi-bin/room.cgi'

print '<html>'

# First, check to see if the room is occupied
# 0 = not occupied
# 1 =     occupied
f = open('../resources.csv', 'rb')
reader = csv.reader(f)
for row in reader:
	occupied = row[2]
f.close()

# If occupied, use URL to call C-program (room.cgi) to regenerate the room the player came from
# Pass player's inventory using REFRESH
if occupied == '1':
	print('''

	<head>
        <meta charset="utf-8">
        <title></title>
        <meta name="description" content="The JEM Room">
        <link rel="stylesheet" href="css/bootstrap.min.css">
        <link rel="stylesheet" href="css/main.css">
    </head>
    <body>
    <div class="container col-lg-6 picture_container">
    </div>
    <div class="container col-lg-6 picture_container">
    </div>
    <div class="container">
    <div class="container col-lg-3">
    </div>

    <div class="jumbotron col-lg-6">
	
	<center> <h1> Room occupied </h1> </center>
    	<p> 
			Sorry, the JEM room is occupied by another player at the moment. <br>
		</p>
		<p>
			You can go back to the room you came from by clicking on the 'Go back' button below.
		</p>
	<center>
		<form action="''' + URL + '''" method="post"> 
				<input type="text" name="command" value="refresh">
        		<input type="hidden" name="inventory" value="'''+ inventory +'''">
        		<input type="submit" value="Go back">
		</form>
    </center>
    <div class="container">
    <div class="container col-lg-3">
    </body>

	''')


# If this room is available, generate it including the player's inventory as a hidden field.
# Two ways to do this:
#	- Calling a.out or room.cgi, or
# 	- Generating the initial page
elif occupied == '0':

	# First, lets split the INVENTORY string, because we need to substract 1 manna from player's inventory
	inv = inventory.split(',')
	manna = int(inv[0])
	gold = int(inv[1])
	manna -= 1

	# If the player has zero manna, game is over.
	if manna <= 0:
		print('''
	<head>
        <meta charset="utf-8">
        <title></title>
        <meta name="description" content="The JEM Room">
        <link rel="stylesheet" href="css/bootstrap.min.css">
        <link rel="stylesheet" href="css/main.css">
    </head>
    <body>
    <div class="container col-lg-6 picture_container">
    </div>
    <div class="container col-lg-6 picture_container">
    </div>
    <div class="container">
    <div class="container col-lg-3">
    </div>

    <div class="jumbotron col-lg-6">


		<div class="inventory">
			<br>
			<p>Gold: <b>'''+ str(gold) +'''</b></p>
			<p>Mana: <b>0</b></p>
		</div>

		<br><br>
	
	<center> <h1> Game over :( </h1> </center>
    	<p> 
			You do not have any manna left, so the game is over. <br>
			It was a good try, though! <br>
		</p>
		<p>
			If you want to start over, click <a href="http://www.cs.mcgill.ca/~hgokse/room.html">here</a>!
		</p>
    
    <div class="container">
    <div class="container col-lg-3">
    </body>''')


	# Check if the transported player wins
	elif gold >= 100:
		print('''
	<head>
        <meta charset="utf-8">
        <title></title>
        <meta name="description" content="The JEM Room">
        <link rel="stylesheet" href="css/bootstrap.min.css">
        <link rel="stylesheet" href="css/main.css">
    </head>
    <body>
    <div class="container col-lg-6 picture_container">
    </div>
    <div class="container col-lg-6 picture_container">
    </div>
    <div class="container">
    <div class="container col-lg-3">
    </div>

    <div class="jumbotron col-lg-6">


		<div class="inventory">
			<br>
			<p>Gold: <b>'''+ str(gold) +'''</b></p>
			<p>Mana: <b>'''+ str(manna) +'''</b></p>
		</div>

		<br><br>

	<center>
		<h1> YOU WIN!!! </h1>
		<h3> Congratulations! </h3>
	</center>
	<p> 
		It looks like you have collected at least 100 gold pieces. <br>
		Good job!
	</p>
	<p>
		If you want to play again, click <a href="http://www.cs.mcgill.ca/~hgokse/room.html">here</a>!
	</p>
    
    <div class="container">
    <div class="container col-lg-3">
    </body>''')








	if manna > 0 and 0 <= gold < 100:
		# Now write the updated manna to the CSV file
		# We are adding 1 to the room's resources
		r = csv.reader(open('../resources.csv'))
		lines = [l for l in r]
		lines[0][0] = int(lines[0][0]) + 1
		# Also change the occupied field to 1
		lines[0][2] = '1'
		writer = csv.writer(open('../resources.csv', 'w'))
		writer.writerows(lines)

		# Lastly, concatenate update manna and gold into inventory
		m = str(manna)
		g = str(gold)
		inventory = m +','+ g

		print('''
	    
		<head>
        <meta charset="utf-8">
        <title></title>
        <meta name="description" content="The JEM Room">
        <link rel="stylesheet" href="css/bootstrap.min.css">
        <link rel="stylesheet" href="css/main.css">
    </head>
    <body>
    <div class="container col-lg-6 picture_container">
    </div>
    <div class="container col-lg-6 picture_container">
    </div>
    <div class="container">
    <div class="container col-lg-3">
    </div>

    <div class="jumbotron col-lg-6">


		<div class="inventory">
			<br>
			<p>Gold: <b>''' + g + '''</b></p>
			<p>Manna: <b>''' + m + '''</b></p>
		</div>

		<br><br>

    <div class="row">

		<center>
			<form action="http://www.cs.mcgill.ca/~syu47/cgi-bin/transporter.py" method="get">
	        	<input type="hidden" name="inventory"  value="''' + inventory + '''">
				<input type="hidden" name="URL"        value="http://cs.mcgill.ca/~hgokse/cgi-bin/room.cgi">
                <input type="hidden" name="successURL" value="http://cs.mcgill.ca/~hgokse/cgi-bin/success.py">
				<input type="submit" value="NORTH">
			</form>
		
			<br><br>

			<form action="http://cs.mcgill.ca/~syu47/cgi-bin/transporter.py" method="get" style= "display: inline">
				<input type="hidden" name="inventory"  value="''' + inventory + '''">
				<input type="hidden" name="URL"        value="http://cs.mcgill.ca/~hgokse/cgi-bin/room.cgi">
                <input type="hidden" name="successURL" value="http://cs.mcgill.ca/~hgokse/cgi-bin/success.py">
               	<input type="submit" value=" WEST ">
			</form>
	 
			&nbsp &nbsp &nbsp

            <form action="http://cs.mcgill.ca/~hgokse/cgi-bin/room.cgi" method="post" style="display: inline">
                <input type="hidden" name="inventory" value="1,0">                
				<input type="text" name="command">
                <input type="submit" value="Submit">
            </form>
       
			&nbsp &nbsp &nbsp
	
			<form action="http://cs.mcgill.ca/~pprade/cgi-bin/transporter.py" method="get" style= "display: inline">
                <input type="hidden" name="inventory"  value="''' + inventory + '''">
                <input type="hidden" name="URL"        value="http://cs.mcgill.ca/~hgokse/cgi-bin/room.cgi">
                <input type="hidden" name="successURL" value="http://cs.mcgill.ca/~hgokse/cgi-bin/success.py">
                <input type="submit" value=" EAST ">
   		    </form>	
 
        	<br><br><br>
        
			<form action="http://cs.mcgill.ca/~syu47/cgi-bin/transporter.py" method="get">
                <input type="hidden" name="inventory"  value="''' + inventory + '''">
                <input type="hidden" name="URL"        value="http://cs.mcgill.ca/~hgokse/cgi-bin/room.cgi">
                <input type="hidden" name="successURL" value="http://cs.mcgill.ca/~hgokse/cgi-bin/success.py">
                <input type="submit" value="SOUTH">
        	</form>
		</center>

    </div>
    <div class="container">
    <div class="container col-lg-3">
    </body>	''')

	# Call source room's success.py to update their resources.csv
	#if source_room_success != None:
		#print (source_room_success)

else:
	print "Uh-oh! Something went wrong."


print '</html>'

