-- Functions
function SaveToLuaFile(filePath, outputString, overwrite)
   print("SaveToLuaFile...")
   local f;						-- The file
   if overwrite == 1 then		-- Wipe the contents with new data
      f = assert(io.open(filePath, "w"))
   elseif overwrite == 0 then	-- Append with new data
      f = assert(io.open(filePath, "a"))
   end
   -- Write to the file
   f:write(outputString)
   -- Close the file
   f:close()
   print("OK")
end

function CalculateDistanceSquare(x1,y1,z1,x2,y2,z2)
	local distanceSquare = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) + (z2 - z1)*(z2 - z1)
	print(distanceSquare)
	return distanceSquare
end

function GetMinMax(...)
	local minValue = -1
	local maxValue = -1
	local avgValue = -1
	local numValues = 0
	for i,v in ipairs(arg) do
		if minValue == -1 then
			minValue = v
		elseif v < minValue then
			minValue = v
		end

		if maxValue == -1 then
			maxValue = v
		elseif v > maxValue then
			maxValue = v
		end
		
		avgValue = avgValue + v
		numValues = numValues + 1
    end
	avgValue = avgValue / numValues
	print(minValue, maxValue, avgValue, numValues)
	return minValue, maxValue, avgValue, numValues
end

-- Game Settings
MouseSensitivity = 5;
-- Keyboard Inputs
moveForward  = "W"
moveBackward = "S"
moveLeft     = "A"
moveRight    = "D"

-- CPlayerInfo start position
CPlayerInfoStartPos = {0,0,10}

-- Sound Settings
SFX = 100
Music = 100

-- Changed Variables (Remove everthing below this to reset to default values, make sure to leave an empty line)
SFX = 69
Music = 75
SFX = 69
Music = 75
SFX = 69
Music = 75
SFX = 69
Music = 75
SFX = 69
Music = 75
SFX = 69
Music = 75
SFX = 73
Music = 75
SFX = 69
Music = 75
SFX = 69
Music = 75
SFX = 84
Music = 75
SFX = 84
Music = 75
SFX = 84
Music = 75
SFX = 84
Music = 75
SFX = 61
Music = 89
SFX = 61
Music = 89
SFX = 61
Music = 89
SFX = 82
Music = 89
SFX = 71
Music = 89
SFX = 71
Music = 89
SFX = 71
Music = 89
SFX = 71
Music = 89
SFX = 71
Music = 89
SFX = 71
Music = 89
SFX = 71
Music = 89
SFX = 71
Music = 55
MouseSensitivity = 7
MouseSensitivity = 1
MouseSensitivity = 10
MouseSensitivity = 7
MouseSensitivity = 7