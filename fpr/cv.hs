kokot a b = a + b

suma:: [Int] -> Int
suma [] = 0
suma [x] = x
suma (x:xs) = x + suma xs