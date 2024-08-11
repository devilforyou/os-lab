echo "Enter a Number"
read n
m=1
while [ $n -gt 0 ]
do
m=$((m*n))
n=$((n-1))
done
echo "Factorial: $m"
