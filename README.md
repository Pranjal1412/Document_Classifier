The Document Classifier is a C++-based application designed to automatically categorize .docx files into predefined classes: Resume, Medical Report, Notes, and Other. It uses an XML parser to extract raw text from the DOCX file’s internal structure, specifically targeting the document.xml content. After text extraction, the classifier performs keyword matching against curated keyword sets for each category to determine the most appropriate classification. If no strong match is found, the file is labeled as "Other."


Key Features:

Parses .docx files using an XML-based approach.

Efficient keyword-based classification logic.

Creates folders for each category and moves files into the appropriate folders.

