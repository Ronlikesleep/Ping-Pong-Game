# Run with:
#
# (Linux & Mac) python3.5 test.py -m ./mygameengine.so
# (Windows) python3.6 test.py -m ./mygameengine.pyd
#
# The program should also run with 'python2.7' but you will have
# to change the 3.5's to 2.7's in your respective build script as
# well as make sure you compiled with 3.5 or 2.7 load flags.
#
# You will see `python3.5-config --includes` for example which corresponds
# to which version of python you are building.
# (In fact, run `python3.5-config --includes` in the terminal to see what it does!)
import mygameengine

# Now use some python libraries for random numbers!
import random


# Initialize SDL
test = mygameengine.SDLGraphicsProgram(400,400)

# Our main game loop
# Note: This is a simple game that loops for 20 iterations and then
#       exits. 
print("Setting up game loop")
initialLeftPaddleX = 5
initialLeftPaddleY = 100
initialRightPaddleX = 375
initialRightPaddleY = 100
initialBallX = 200
initialBallY = 200
ballRadius = 5
ballXVelocity = 3
ballYVelocity = 3
LEFT_BOUND = 0
RIGHT_BOUND = 400

def paddleMoveControl():
    global initialLeftPaddleY, initialRightPaddleY
    if test.isLeftPaddleUpKeyDown() and initialLeftPaddleY>=0:
        initialLeftPaddleY -= 5
    if test.isLeftPaddleDownKeyDown() and initialLeftPaddleY<=200:
        initialLeftPaddleY += 5

    if test.isRightPaddleUpKeyDown() and initialRightPaddleY>=0:
        initialRightPaddleY -= 5
    if test.isRightPaddleDownKeyDown() and initialRightPaddleY<=200:
        initialRightPaddleY += 5

def detect_collision_with_paddles():
    global ballXVelocity, ballYVelocity, initialBallX, initialBallY
    if initialLeftPaddleX < initialBallX < initialLeftPaddleX + 20 and initialLeftPaddleY < initialBallY < initialLeftPaddleY + 200:
        ballXVelocity = -1*ballXVelocity
    
    if initialBallX > initialRightPaddleX and initialRightPaddleY < initialBallY < initialRightPaddleY + 200:
        ballXVelocity = -1*ballXVelocity

def detect_collision_with_borders():
    global ballXVelocity, ballYVelocity, initialBallX, initialBallY

    if initialBallX <= LEFT_BOUND + ballRadius or initialBallX >= RIGHT_BOUND - ballRadius:
        initialBallX = 200
        initialBallY = 200
        ballXVelocity = 3
        ballYVelocity = 3
    
    if initialBallY <= 0 + ballRadius or initialBallY >= 400 - ballRadius:
        ballYVelocity = -1*ballYVelocity  

gameQuit = False
while(gameQuit==False):
    test.clear()
    test.DrawPaddle(initialLeftPaddleX, initialLeftPaddleY, 20, 200)
    test.DrawPaddle(initialRightPaddleX, initialRightPaddleY, 20, 200)
    test.DrawBall(initialBallX, initialBallY, ballRadius)

    paddleMoveControl()
    detect_collision_with_paddles()
    detect_collision_with_borders()

    initialBallX += ballXVelocity
    initialBallY += ballYVelocity

    test.delay(20)
    test.flip()
    gameQuit = test.poll()
