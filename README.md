AI2-KMeans
==========

Second assignment for Artificial Intelligence 2. 


<h1>Assignment B: Text classification</h1>
This is an individual assignment. This assignment counts 10% of the total grade.

<h2>The concept</h2>
The idea is to classify text by using the K-means algo.  You will classify a selection of content from the open part of Facebook. Focus is on commercial venues like Elkjøp, Expert, Amazon etc.  The idea is to classify customer feedback, learn what the customers are preoccupied with and what they feel about service , products etc. The latter is called sentiment analysis.

<h2>The task</h2>
You should prove that a computer is able to process text and assign tags to them automatically. The task is to define a set of classes up front.  You will create two classification processes. One will be a regular topic sorter. The other will be a sentiment classifier. The topic sorter should consist of 4 classes each referring to a specific product. You will choose which product to focus at. In addition to these four you will add a fifth class called Service.  For the sentiment analysis you create a class called Praise and another one called Shame.

Solicit from Facebook suitable texts for training and testing.  You should download or copy 25-30 texts for trial and have your program parse, classify and sort the texts according to the classes given.  Each class should be seeded with a prototype feature vector characterizing the specific class that it represents.  Based on the K-means algo you will allocate the remaining texts to the classes defined. To what extent you would like to preprocess and filter the text first is your choice.  Once done the program should make a count of each group of classes and provide an inventory of which text belongs to which group.  