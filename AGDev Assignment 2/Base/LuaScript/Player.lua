-- Keyboard Inputs
moveForward  = "W"
moveBackward = "S"
moveLeft     = "A"
moveRight    = "D"

-- CPlayerInfo start position
CPlayerInfoStartPos = {0,0,10}

-- Functions
function CalculateDistanceSquare(x1,y1,z1,x2,y2,z2)
	local distanceSquare = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) + (z2 - z1)*(z2 - z1)
	print(distanceSquare)
	return distanceSquare
end