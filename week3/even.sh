echo "Enter a Number"
read n
if [ $((n%2)) -eq 0 ] 
then
echo "$n is Even"
else
echo "$n is Odd"
fi
