echo "Enter an Year"
read n
if [ $((n%400)) -eq 0 ] 
then
echo "$n is Leap Year"
else
if [ $((n%4)) -eq 0 ]
then
echo "$n is Leap Year"
else
echo "$n is Not a Leap Year"
fi
fi
