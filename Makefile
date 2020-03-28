all: publish

publish:
	gitbook build ./
	cp -r _book/* ../
	rm -rf _book
