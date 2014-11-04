for i in $* 
do
	git rm ${i}
done
git commit
git push
