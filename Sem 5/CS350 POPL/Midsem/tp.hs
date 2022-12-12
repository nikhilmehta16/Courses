import Distribution.Simple.Utils (xargs)
mysum xs = foldr (+) 0 xs

double x = 2*x
quadruple x = double (double x)

-- avg ns = sum ns `div` length ns

zeroto :: (Num a, Enum a) => a -> [a]
zeroto n = [0..n]

-- mylength = foldr inc 0 where inc _ y = 1+y 
z = a `div` length xs
    where
     a = 10
     xs = [1,2,3,4]
signu n
  | n < 0 = -1
  | n == 0 = 0
  | otherwise = 1

--   \ as lambda in haskel
f x = (x*x)

-- minpt f a b
--     | a>b = "Invalid Range"
--     | otherwise = foldr (min . f) 0 [a .. b]

minpt f x y = if x > y
                then
                 error "Invalid range"
            else snd (minimum (zip (map f [x .. y]) [x .. y]))

theAnswer (xs) = all (==42) xs


f = \x -> x (\y -> x y)

g = \x -> (\y -> y) x

join ys [] = ys
join ys (z:zs) = z :(join ys zs)

a = 42:a
b = [1]
checkA xs ys = theAnswer xs && theAnswer ys
checkB xs ys = theAnswer (join xs ys)

-- polar n = 
-- a = 