factorial :: Int -> Int
factorial 0 = 1
factorial 1 = 1
factorial n = n * factorial(n-1)

leapYear :: Int -> Bool
leapYear x = mod x 4 == 0 && mod x 100 /= 0 || mod x 400 == 0

combinations :: Int -> Int -> Int
combinations x y = div (factorial x)  (factorial y * factorial (x-y))
