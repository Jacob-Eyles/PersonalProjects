import random
import time

class deck():
	"""docstring for deck"""
	def __init__(self, decklist):
		self.decklist = decklist
	
	def __str__(self):
		return(str(self.decklist))

	def shuffledeck(self):

		end = random.randrange(3,20)

		for i in range(1,end):
			random.shuffle(self.decklist)

	def drawcard(self):
		card = self.decklist.pop(0)
		self.decklist.append(card)
		return card

	def restore(self,decklist):
		self.decklist = decklist
		self.shuffledeck()

class hand():
	""" """
	def __init__(self, handlist):
		self.handlist = handlist

	def __str__(self):
		return str(self.handlist)

	def __len__(self):
		return len(self.handlist)

	def __getitem__(self,index):
		return self.handlist[index]

	def addcard(self, card):
		self.handlist.append(card)

	def sum_first(self):
		card = self.handlist[0]
		total = 0

		if card[0] == 'A':
			if total <= 10:
				total += 11
			else:
				total += 1

		elif card[0] in 'JKQ':
			total += 10
		else:
			total += int(card[0])

		return total

	def sum(self):
		total = 0
		for card in self.handlist:
			if card[0] == 'A':
				if total <= 10:
					total += 11
				else:
					total += 1

			elif card[0] in 'JKQ':
				total += 10
			else:
				total += int(card[0])

		return total

class bank():
	""" """
	def __init__(self, name, amount):
		self.amount = amount
		self.name = name

	def betchips(self, betamount):
		if betamount <= self.amount:
			self.amount = self.amount - betamount
			print(f'{self.name}, you have bet {betamount} chips!\nYou have {self.amount} chips left.')
		else:
			print(f'You do not have enough chips to bet this amount ({betamount}).\nYou have {self.amount} chips left.')

	def addchips(self,addamount):
		self.amount += addamount
		#print(f'{self.name}, your chips total is now {self.amount}.')

	def __str__(self):
		print(f'{self.name},you have {self.amount} chips avaliable...')

def card_hand_player(plist):
    
    #create the player hand
	lengthp = len(plist)
	string10 = '-----------  '*(lengthp)
	string11 = ''
	string12 = '|         |  '*(lengthp)
	string13 = string12
	string14 = ''
	string15 = string12
	string16 = string12 
	string17 = ''
	string18 = string10

	for i in range(0,lengthp):
		card = plist[i]

		stringm = f'|    {card[0]}    |  '
		stringt = f'|{card[1]}        |  '
		stringb = f'|        {card[1]}|  '

		string11 = string11 + stringt
		string14 = string14 + stringm
		string17 = string17 + stringb

	print(string10)
	print(string11)
	print(string12)
	print(string13)
	print(string14)
	print(string15)
	print(string16)
	print(string17)
	print(string18)

def card_hand_computer(clist):

    #create the computer hand
	lengthc = len(clist)
	string1 = '-----------  '*(lengthc)
	string2 = ''
	string3 = '|         |  '*(lengthc)
	string4 = string3
	string5 = ''
	string6 = string3
	string7 = string3
	string8 = ''
	string9 = string1

	for i in range(0,lengthc-1):
		card = clist[i]

		stringm = f'|    {card[0]}    |  '
		stringt = f'|{card[1]}        |  '
		stringb = f'|        {card[1]}|  '

		string2 = string2 + stringt
		string5 = string5 + stringm
		string8 = string8 + stringb

	stringm = '|    ?    |  '
	stringt = '|BJ       |  '
	stringb = '|       BJ|  '

	string2 = string2 + stringt
	string5 = string5 + stringm
	string8 = string8 + stringb

	print(string1)
	print(string2)
	print(string3)
	print(string4)
	print(string5)
	print(string6)
	print(string7)
	print(string8)
	print(string9)

def playing_board(phandlist,chandlist,betamount,chipamount,Round,turn):

	#now display the two card sets...
	print('\n'*100)
	print('(:____BlackJack____xD\n')
	print(f'Round:{Round:{12}}\nChips remaining:{chipamount:{4}}\nCurrent Bet:{betamount:{7}}')

	if turn==1:
		print(f"\n\nComputer's hand:{chandlist.sum_first():{3}}\n\n")
		card_hand_computer(chandlist)
	else:
		print(f"\n\nComputer's hand:{chandlist.sum():{3}}\n\n")
		card_hand_player(chandlist)
	
	print(f"\n\nPlayer's hand:{phandlist.sum():{5}}\n\n")
	card_hand_player(phandlist)

	if turn == 1:
		return phandlist.sum(),chandlist.sum_first()
	else:
		return phandlist.sum(),chandlist.sum()

def intro():
	print('\nWelcome to BlackJack !!!')
	print('\n\nBeat the computer by getting the closest to 21...')
	charc = input('\n\nPress ENTER to play...')
	time.sleep(0.3)
	print('3 . . .')
	time.sleep(0.3)
	print('2 . . .')
	time.sleep(0.3)
	print('1 . . .')
	time.sleep(0.3)
	print('GO ! ! !')

def reset(decktype,decklist):

	#decktype.restore(decklist)
	#decktype.shuffledeck()
	phand = hand([deck.drawcard(),deck.drawcard()])
	chand = hand([deck.drawcard(),deck.drawcard()])

	return phand,chand
	
###################################################

#setup variables etc...

intro()
count = 1
turn = 1
chips = 100
decklist = ['AH','AC','AD','AS','2H','2C','2D','2S','3H','3C','3D','3S'
,'4H','4C','4D','4S','5H','5C','5D','5S','6H','6C','6D','6S'
,'7H','7C','7D','7S','8H','8C','8D','8S','9H','9C','9D','9S'
,'JH','JC','JD','JS','QH','QC','QD','QS','KH','KC','KD','KS']

time.sleep(0.5)
print('\n'*50)
deck = deck(decklist)
deck.shuffledeck()
phand, chand = reset(deck,decklist)

print('The deck is being shuffled...')
time.sleep(0.9)
print('\n'*50)

###################################################

namep = input('Please enter your name: ')
bank = bank(namep, 100)

print('\nYou have 100 chips to start with...')

Round = 1
nturns = 1

while True:

	if Round%3 == 0:
		deck.shuffledeck()

	if nturns == 1:
		while True:
			try:
				current = bank.amount
				betamount = int(input('\nHow many chips would you like to bet? '))
				if betamount>current or betamount == 0:
					continue
					print(f'You do not have enough chips to bet this amount ({betamount}).\nYou have {current} chips left.')
				else:
					bank.betchips(betamount)
					if Round>1:
						phand,chand = reset(deck,decklist)
					break
			except(ValueError):
				print("Please enter your bet again!\n")
				continue


	if turn == 1:

		ptotal,ctotal = playing_board(phand,chand,betamount,bank.amount,Round,turn)

		if ptotal == 21:
			print("Your total is twenty one!\n\n---BLACKJACK---\nNow it is the computer's turn...")
			turn = 0
			nturns += 1
		elif ptotal<21:
			while True:
				try:
					hit = input(f"Your current total is {ptotal}.\nWould you like to 'hit' ('h')-(add another card), or 'stand' ('s')-(keep your current total)?")
					if hit in 'hH':
						phand.addcard(deck.drawcard())
						nturns += 1
						break
					elif hit in 'sS':
						print(f"OK. Your final total is {ptotal}.\nNow it is the computer's turn...")
						turn = 0
						nturns += 1
						break
				except:
					print('Please enter your response again...\n')
					continue
		else:
			print(f'Your total of {ptotal} is over 21!\nYou have gone BUST!\nYour total is now {bank.amount} chips.')
			Round += 1
			nturns = 1
			turn = 1

	if turn == 0:

		ctotal = chand.sum()

		while ctotal<17:

			chand.addcard(deck.drawcard())
			ctotal = chand.sum()

		ptotal,ctotal = playing_board(phand,chand,betamount,bank.amount,Round,turn)

		if ptotal == ctotal:
			bank.addchips(betamount)
			print(f"\nIt's a draw!!!\nYour bet will be refunded...\nYour total is now {bank.amount} chips.")
			Round += 1
			turn = 1
			nturns = 1

		elif (ptotal > ctotal) or ctotal>21:
			bank.addchips(betamount*2)
			print(f"\nYou win!!!\nYou won {betamount} chips...\nYour total is now {bank.amount} chips.")
			turn = 1
			Round += 1
			nturns = 1

		elif ptotal < ctotal:
			print(f"\nYou lose!!!\nYou lost {betamount} chips...\nYour total is now {bank.amount} chips.")
			turn = 1
			Round += 1
			nturns = 1
	
	if bank.amount <=0 and nturns == 1:
		
		print(f'You have no chips left!!!\nYou survived {Round} rounds :)')
		yn = input('\n\nWould you like to play again? (yes or no)')

		if yn in 'yesYES':
			turn = 1
			Round = 1
			nturns = 1
			diff = 100 - bank.amount
			bank.addchips(diff)
			print('Your total is now 100 chips.')
		else:
			turn = 2

	if turn == 2:
		break

print(f'Thanks for playing, {bank.name}')
