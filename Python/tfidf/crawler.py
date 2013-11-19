
#!/usr/bin/python

#
# The Crawler
#


from __future__ import with_statement
from contextlib import closing
from HTMLParser import HTMLParser

import gzip
import shelve
import math
import sys
import urlmanager
import re

#class myParser(HTMLParser):

class WebNode(HTMLParser):

    words = dict()
    wc    = 0

    title = ''
    settitle = False
    neighborlist = dict()
    setneighbor  = ''

    def handle_starttag(self,tag, attrs):
        realtag = tag.lower()
        if   realtag == "title" : # and ('type', 'story') in attrs:
            self.settile = True
        elif realtag == "a":
            for (x, y) in attrs:
                if x == "href":
                    self.setneighbor = y
                    self.neighborlist[self.setneighbor] = ''

    def handle_endtag(self, tag):
        pass

    def handle_data(self,data):
        if self.settitle:
            self.title   = data
            self.settitle = False

        if self.setneighbor:
            self.neighborlist[self.setneighbor] = data
            self.setneighbor = ''

        dwords = data.upper().split()
        for ew in dwords:
            ew = ew if ew.isalpha() else ''.join(re.split('\W|\d', ew))
            self.wc += 1
            try:
                self.words[ew] += 1
            except:
                self.words[ew]  = 1

    def readself(self, url):
        """Just read the content of the URL and feed it to the Parser,
        which is self"""
        urlf = urlmanager.openurl(url)
        if urlf:
            mycontent = urlf.read()
            try:
                self.feed(mycontent)
                return True
            except:
                return False

    tfs = dict() # Better create a shelf
    def docalculations(self):
        """Calculate the tf values for each word in the WebNode/Page"""
        for (ew, occ) in self.words.iteritems():
            self.tfs[ew] = occ * 2**32 * 1.0 / self.wc
        self.words.clear() # We don't need it anymore. Do we?

    def prepareneighborlist(self):
        urlp  = re.compile('(http:\/\/.+)(.+\.(htm.?|com|info|de|php|stm))?(\/)?', re.IGNORECASE)
#        urltp = re.compile('<a (?:.*?)href="(\S*?)">(.*?)</a>', re.DOTALL)
        stem = urlp.match(self._name).group(1)
        if stem[-1] != '/':
            stem += '/'

        for en in self.neighborlist.keys():
            if not urlp.match(en):
                self.neighborlist[stem + en] = self.neighborlist[en]
                self.neighborlist.pop(en)

    def setup(self, name, alias=''):
        print "Opening ", name, "as ", alias
        self._name     = name
        self.title     = alias
        self.tfs = {}
        if self.readself(name):
            self.docalculations()
            self.prepareneighborlist()
        #    print len(self.tfs)
        return self.neighborlist

    def __str__(self):
        return repr(self._name)

    def add_neighbor(self, j, jdescri=''):
        self.neighborlist[j] = jdescri


import os
class WebGraph(object):
    def __init__(self, levels=999): # Adjust it to make infinity
        self.nodes = dict()
        self.levels = levels

    def add_node(self, i, alias='', level=0):
        if level == self.levels:
            return False
        if i not in self.nodes:
            self.nodes[i] = WebNode()
            neighborstobe = self.nodes[i].setup(i, alias)
            for en, ena in neighborstobe.items():
                if self.add_node(en, ena, level+1):
                    self.add_edge(i, en)

#    tfidfs = dict()

    def collect_words(self):
        D = len(self.nodes)
        for node in self.nodes.itervalues():
            nname = node._name
            for wd, octfs in node.tfs.iteritems():
                if wd in self._tfidf:
                    x = self._tfidf[wd] + list([(octfs, nname)])
                    self._tfidf[wd] = x
                else:
                    self._tfidf[wd] = list([(octfs, nname)])


    def compute_tfidf(self):
        D = len(self.nodes)
        for wd, item in self._tfidf.iteritems():
            Dext, Rext = self.tfidfs.get(wd, [0, []])
            Di  = len(item) + Dext
            idf = math.log(D*1.0/Di) # check this
            Rst = [ (x[0] * idf, x[1]) for x in item] + Rext
            Rst.sort()
            Rst.reverse()
            self.tfidfs[wd] = [Di, Rst]

    def create_tfidf(self):
        self._tfidf = shelve.open(os.tmpnam())
        self.collect_words()
        self.tfidfs = shelve.open('.tfidfsfileforcrawler')
        self.compute_tfidf()
        self._tfidf.close()

    def add_edge(self, i, j, ialias='', jalias=''):
        if i not in self.nodes:
            self.add_node(i, self.levels-1)
        if j not in self.nodes:
            self.add_node(j, self.levels-1)
        self.nodes[i].add_neighbor(self.get_node(j))

    def get_node(self, i):
        return self.nodes.get(i, None)

    def has_edge(self, i, j):
        return j in self.nodes.get(i, WebNode('')).neighbors
        # One might want to look up the ``get'' method of dicts in
    # python. This was not disussed in the lecture.

    def nodes(self):
        return self.nodes.keys()

    def edges(self):
        for i, iN in self.nodes.iteritems():
            for j in iN.neighbors:
                yield (i, j.name)


# The graph shall be created by specifying the default level of
# recursion. It would have been better to move it to each page's
# preference. Well so it is. And edges could be added and tfidf would be
# updated (BUG: TODO: if a page comes a second time, it will get added
# again to the list of pages for every word in it - easy to debug, but
# lazy. And after all the operations, the shelf is created and could be
# closed. Next time you open the thing, it will still be ready for use.
# MAKE SURE TO CALL Graph.tfidfs.close() at the end.

import sys
print "Creating WebGraph.....",
G = WebGraph(1)#int(sys.argv[1]))
print "Created."
G.add_node("http://news.bbc.co.uk", "BBC")
#G.add_node(sys.argv[2], sys.argv[3])
G.create_tfidf()
for x,y  in G.tfidfs.iteritems():
    print x, "-", y

G.tfidfs.close()
