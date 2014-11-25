for i in $* 
do
	git add ${i}
done
git commit -a
git push https://github.com/chwebteam1/OSP3A.git
