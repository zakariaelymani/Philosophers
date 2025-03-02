while true;
do
	sleep 600 

	arsh=$(uname -a)

	vcpu=$(nproc)

	cpus=$(lscpu | grep "Socket(s)" | wc -l)

	total=$(df --total -h | grep "total" | awk '{print $2}')
	disc=$(df --total -m | grep "total" | awk -v var="$total" '{printf("%d/%dGb (%.2f%%)",$3,var,$3/$2*100)}')

	lvm=$(lsblk | grep -q "lvm" && echo "yes" || echo "no")

	tcp=$(netstat -t | grep ESTABLISHED | wc -l )

	users=$(users | wc -l)


	boottime=$(who -b | awk '{printf($3 " " $4)}')

	mem=$(free -m | grep Mem | awk '{printf("%d/%dMB(%d%%)",$3,$2,$3/$2*100)}')

	ip=$(hostname -I)
	amac=$( ip link | grep link/ether | awk '{print $2}')

	load=$(top -bn1 | grep "%Cpu(s):"  | awk '{printf("%d%%",$2 + $4)}')

	sudolog=$(cat /var/log/sudo/sudo_config | grep COMMAND | wc -l)

	wall "
	   #Architectur:$arsh
	   #CPU physical:$cpus
	   #vCPU:$vcpu
	   #Memory Usage:$mem
	   #Disk Usage: $disc
	   #CPU load: $load
	   #Last boot: $boottime
	   #LVM use: $lvm 
	   #Connections TCP: $tcp ESTABLISHED 
	   #User log: $users
	   #Network: IP $ip $amac
	   #Sudo : $sudolog cmd   

	"
done

