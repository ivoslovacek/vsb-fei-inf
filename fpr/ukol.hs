compareString :: String -> String -> Bool
compareString [] []  = True
compareString (x:xs) (y:ys) | x == y = compareString (xs) (ys)
                            | otherwise = False

charToString :: Char -> String
charToString c = [c]

replaceChars :: Char -> [(Char, String)] -> String
replaceChars x [(y,z)] | x == y = z
                       | otherwise = charToString x
replaceChars x ((y,z):ys) | x == y = z
                          | otherwise = replaceChars x ys

createNewString :: String -> [(Char, String)] -> String
createNewString [] [] = []
createNewString [x] y = replaceChars x y
createNewString (x:xs) y = replaceChars x y ++ createNewString xs y

decode :: String -> [(Char,String)] -> String
decode [] _ = []
decode x [] = x
decode x y | compareString x (createNewString x y) = x
           | otherwise = decode (createNewString x y) y