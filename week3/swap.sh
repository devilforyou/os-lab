echo "Enter Number 1"
read a
echo "Enter Number 2"
read b
a=$((a+b))
b=$((a-b))
a=$((a-b))
echo "Number 1 : $a , Number 2 : $b"
