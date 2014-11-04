for i in $* 
do
	git add ${i}
done
git commit
git push
