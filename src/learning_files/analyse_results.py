path = "./"


f = open(path + "learning_player_log.txt", 'r')
lines = f.read().splitlines()
try:
	third_last_line = lines[-3]
except:
	third_last_line = ""
toChangeBestWeights = False
if third_last_line == "YOU WIN!":
    toChangeBestWeights = True
f.close()

if toChangeBestWeights:
    currentWeightFile = open(path + "current_weights.txt", 'r')
    weights = currentWeightFile.read().splitlines()
    weights = weights[0]
    weights = weights + '\n'
    currentWeightFile.close()
    bestWeightFile = open(path + "best_weights.txt", 'w')
    bestWeightFile.write(weights)
    bestWeightFile.close()
    bestWeightChangesRecord = open(path + "best_weights_history.txt", 'a')
    bestWeightChangesRecord.write(weights)
    bestWeightChangesRecord.close()