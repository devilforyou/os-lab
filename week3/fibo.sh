echo "Enter Number"
read c
a=0
b=1
t=0
echo "0"
echo "1"
for (( i=1 ; i<=$c ; i++ )); 
do
	t=$((a+b))
	echo "$t"
	a=$b
	b=$t
done
