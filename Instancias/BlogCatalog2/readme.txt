Social Computing Data Repository - Basic Information
==========================================================================
Dataset Name: BlogCatalog
Abstract: BlogCatalog is the social blog directory which manages the bloggers and their blogs.
Number of Nodes: 97,884
Number of Edges: 2,043,701
Missing Values: No

Source:
==========================================================================
Reza Zafarani*, Huan Liu*
Connecting Corresponding Identities across Communities, 3rd International AAAI Conference on Weblogs and Social Media (ICWSM09), May 17-20, 2009. San Jose, California.

* School of Computing, Informatics and Decision Systems Engineering, Arizona State University. E-mail: reza@asu.edu, huan.liu@asu.edu

Data Set Information:
==========================================================================
[I]. Brief description
This is the data set crawled on June, 2010 from BlogCatalog ( http://www.blogcatalog.com ). BlogCatalog is a social blog directory website. 
This contains the friendship network crawled. For easier understanding, all the contents are organized in CSV file format.

[II]. Basic statistics
Number of bloggers : 97,884
Number of friendship pairs: 2,043,701

[III]. The data format

2 files are included:

1. nodes.csv
-- it's the file of all the users. This file works as a dictionary of all the users in this data set. It's useful for fast reference. It contains
all the node ids used in the dataset

2. edges.csv
-- this is the friendship network among the bloggers. The blogger's friends are represented using edges. Here is an example. 

1,2

This means blogger with id "1" is friend with blogger id "2".

Relevant Papers:
==========================================================================

1. Nitin Agarwal, Huan Liu, Sudheendra Murthy, Arunabha Sen, and Xufei Wang. "A Social Identity Approach to Identify Familiar Strangers in a Social Network", 3rd International AAAI Conference on Weblogs and Social Media (ICWSM09), pp. 2 - 9, May 17-20, 2009. San Jose, California. 