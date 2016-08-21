A simple search engine that crawls and indexes a series of webpages using a reverse index data structure
---------------------------------------------------------------------------------------------------------
I implemented a set of classes that aided in downloading webpages from the internet, and indexing them in an efficient manner for fast querying. Generally, each class had an implementation version and a wrapper class. Without listing the implemention file, these are the classes:
- MyMap
- WordBag
- Indexer
- WebCrawler
- Searcher

A short description of how each class is used is commented on their respective implementation headers (eg. WordBagImpl.h, IndexerImpl.h). As an overview, WordBag holds the contents of a webpage, Indexer organizes WordBags into indexes, WebCrawler downloads new webpages to store in an Indexer, and Searcher searches through the indexes and returns a list of results.

Full specs for this project can be found [here](https://github.com/nehcney/Search-Engine/blob/master/spec.doc).

Copyright (c) 2016 Yen Chen
