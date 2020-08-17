def printboard(markerlist):

	print('         |         |         ')
	print(' {0:^8}| {1:^8}| {2:^8}'.format(markerlist[0], markerlist[1], markerlist[2]))
	print('         |         |         ')
	print('-'*30)
	print('         |         |         ')
	print(' {0:^8}| {1:^8}| {2:^8}'.format(markerlist[3], markerlist[4], markerlist[5]))
	print('         |         |         ')
	print('-'*30)
	print('         |         |         ')
	print(' {0:^8}| {1:^8}| {2:^8}'.format(markerlist[6], markerlist[7], markerlist[8]))
	print('         |         |         ')

def makemove(markerlist):
	good = True

	number = input('Please pick a tile number (1-9): ')

	while good == True:
		if (number in '123456789') and (markerlist[int(number)-1] == ' '):
			return int(number)-1
		else:
			number = input(f'Tile {number} is not avaliable:\nPlease choose another tile (1-9): ')

def checkboard(tile):
	won = 0
	count = 0

	if tile[0] == tile[1] and tile[0] == tile[2] and tile[0] != ' ':
		won = 1
	if tile[3] == tile[4] and tile[3] == tile[5] and tile[3] != ' ':
		won = 1
	if tile[6] == tile[7] and tile[6] == tile[8] and tile[6] != ' ':
		won = 1
	if tile[0] == tile[3] and tile[0] == tile[6] and tile[0] != ' ':
		won = 1
	if tile[1] == tile[4] and tile[1] == tile[7] and tile[1] != ' ':
		won = 1
	if tile[2] == tile[5] and tile[2] == tile[8] and tile[2] != ' ':
		won = 1
	if tile[0] == tile[4] and tile[0] == tile[8] and tile[0] != ' ':
		won = 1
	if tile[2] == tile[4] and tile[2] == tile[6] and tile[2] != ' ':
		won = 1

	for num in tile:
		if num != ' ':
			count += 1

	if (count == 9 and won == 0):
		won = 2

	return won

def winner(won):
	play = True

	if won == 2:
		yon = input('The game is a draw...\nWould you like to play again? (yes or no) ')
		if yon == 'no' or yon == 'No':
			play = False

	if won == 1:
		if count%2 == p1:
			yon = input('Congratulations player one! \nWould you like to play again? (yes or no) ')
			if yon == 'no' or yon == 'No':
				play = False
		else:
			yon = input('Congratulations player two! \nWould you like to play again? (yes or no) ')
			if yon == 'no' or yon == 'No':
				play = False

	return play

def playertime():
	global p1mark
	global p2mark

	marker = input("Please pick a marker 'X' or 'O': ")
	player = int(input('\nWhich player (1 or 2) would you like to be? '))

	if marker == 'X' or marker == 'x':
		if player == 1:
			p1mark = 'X'
			p2mark = 'O'
		else:
			p2mark = 'X'
			p1mark = 'O'
	else:
		if player == 1:
			p1mark = 'O'
			p2mark = 'X'
		else:
			p1mark = 'X'
			p2mark = 'O'


#################################################

print('Welcome to TIC TAC TOE\n\n')

playertime()
import time
p1 = 1
p2 = 0

play = True

while play:
	markerlist = [' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ']
	won = 0
	print('Player 1 shall go first...\n\n\n')

	while won == 0:

		count = 0
		time.sleep(0.2)
		print('\n'*100)
		printboard(markerlist)
		index = makemove(markerlist)

		for tile in markerlist:
			if tile == ' ':
				count += 1

		if count%2 == p1:
			markerlist[index] = p1mark
		else:
			markerlist[index] = p2mark

		won = checkboard(markerlist)

	print('\n'*100)
	printboard(markerlist)
	play = winner(won)

	if play:
		again = input("Would you like to reassign symbols? (yes or no) ")

		if again == 'yes' or again == 'Yes':
			playertime()
			