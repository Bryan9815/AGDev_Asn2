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

-- Variables
title = "DM2240 - Assignment 2"
width = 1600
height = 900

windowMode = 1;
-- 0 = Fullscreen, 1 = Windowed
Resolution = 3;
-- 0 = 800x600, 1 = 1024x720, 2 = 1440x810, 3 = 1600x900, 4 = 1600x1024, 5 = 1920x1080
MouseSensitivity = 5

-- Changed Variables (Remove everthing below this to reset to default values, make sure to leave an empty line)
windowMode = 1
Resolution = 3
width = 1600
height = 900
windowMode = 1
Resolution = 3
MouseSensitivity = 1
width = 1600
height = 900
windowMode = 1
Resolution = 3
MouseSensitivity = 10
width = 1600
height = 900
windowMode = 1
Resolution = 3
MouseSensitivity = 7
width = 1600
height = 900
windowMode = 1
Resolution = 3
MouseSensitivity = 7
width = 1600
height = 900
windowMode = 1
Resolution = 2
MouseSensitivity = 7
width = 1440
height = 810
windowMode = 1
Resolution = 2
MouseSensitivity = 7
width = 1440
height = 810
windowMode = 1
Resolution = 2
MouseSensitivity = 7
width = 1440
height = 810
windowMode = 1
Resolution = 1
MouseSensitivity = 7
width = 1024
height = 720
windowMode = 1
Resolution = 3
MouseSensitivity = 7
width = 1600
height = 900
windowMode = 1
Resolution = 3
MouseSensitivity = 7
width = 1600
height = 900
windowMode = 1
Resolution = 3
MouseSensitivity = 7
width = 1600
height = 900
windowMode = 1
Resolution = 3
MouseSensitivity = 7
width = 1600
height = 900
windowMode = 1
Resolution = 3
MouseSensitivity = 7
width = 1600
height = 900
windowMode = 1
Resolution = 3
MouseSensitivity = 7
width = 1600
height = 900
windowMode = 0
Resolution = 3
MouseSensitivity = 7
width = 1600
height = 900
windowMode = 0
Resolution = 3
MouseSensitivity = 7
width = 1600
height = 900
windowMode = 0
Resolution = 3
MouseSensitivity = 7
width = 1600
height = 900
windowMode = 1
Resolution = 0
MouseSensitivity = 7
width = 800
height = 600
windowMode = 1
Resolution = 2
MouseSensitivity = 7
width = 1440
height = 810
windowMode = 1
Resolution = 2
MouseSensitivity = 7
width = 1440
height = 810
windowMode = 1
Resolution = 2
MouseSensitivity = 1
width = 1440
height = 810
windowMode = 1
Resolution = 2
MouseSensitivity = 7
width = 1440
height = 810
windowMode = 1
Resolution = 2
MouseSensitivity = 7
width = 1440
height = 810
windowMode = 1
Resolution = 2
MouseSensitivity = 7
width = 1440
height = 810
windowMode = 1
Resolution = 2
MouseSensitivity = 7
width = 1440
height = 810
