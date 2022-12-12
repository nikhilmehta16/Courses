mysum xs = foldr (+) 0 xs

double x = 2*x
quadruple x = double (double x)

-- avg ns = sum ns `div` length ns

zeroto :: (Num a, Enum a) => a -> [a]
zeroto n = [0..n]

mylength = foldr inc 0
       where inc _ y = 1+y 