type Pic = [String]

pic :: Pic
pic = [ "....#....",
        "...###...",
        "..#.#.#..",
        ".#..#..#.",
        "....#....",
        "....#....",
        "....#####"]



pp :: Pic -> IO()
pp x = putStr (concat (map (++"\n") x))

flipV :: Pic -> Pic
flipV  = map reverse

flipH :: Pic -> Pic
flipH  = reverse

above :: Pic -> Pic -> Pic
above x y = x ++ y

sideBySide :: Pic -> Pic -> Pic
sideBySide (x:xs) (y:ys) = (x++y):sideBySide xs ys
sideBySide _ _  = []

toColumn :: String -> Pic
toColumn str = [[x]|x<-str]

rotateR :: Pic -> Pic
rotateR [] = []
rotateR [x] = toColumn x
rotateR (x:xs) = sideBySide (rotateR xs) (toColumn x)

rotateL :: Pic -> Pic
rotateL [] = []
rotateL [x] = toColumn x
rotateL (x:xs) = sideBySide (rotateL xs) (toColumn x)