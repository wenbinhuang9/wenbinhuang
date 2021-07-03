
# Web and Front End Evolution 

## Static Website

Initially, the website are just simple static contents , no any interaction with users. So the web is majorly oriented for content sharing on the Internet. 

At this time, the front end techs is also very simple, HTML is enough for web based document sharing on the Internet. 

## Dynamic Website and Interactivity 

With Internet development, the website enables more interactions with user like socialization, shopping etc. Javascript and DOM plays a key role for the interaction. 

Javascript was created by Netscape Communications in 1995 to enable interactivity. 

When a user clicks a mouse, a click event is generated. And event callback function is executed, and then callback result is to applied onto DOM, and DOM is rerendered by browser. 

At this time ,the front end techs is evolved by Javascript and also DOM. 

## Ajax
Previously, when a user clicks an event, the page has to be refreshed. The browers is to refresh the page by laoding the wholely new page. When we only need to refresh part of small data, the price is to be very high and performance is to be very low.  

Ajax solves this issue by retrieving data from a server asynchronously (in the background) without interfering with the display and behaviour of the existing page, in other words, we can refresh the data to the current page without loading a wholely new page. 

Ajax is a collection of techniques including 

1. HTML for view 
2. DOM for interaction
3. JSON or XML as a dataformat enabling network data exchange 
4. XMLHttpRequest object  for asynchronous communication
5. JavaScript brings these technologies together by accepting event from user, executing XMLHttpRequest to request data from server asynchronously, parsing Json, applying Json data onto DOM. 

Ajax is the miletone of front end techs to improve the user experience by reducing page refreshing time. 

## Jquery 

Enabling interactivity using native javascript DOM APIs is very painful. From one hand, different browers have different DOM standards. From the other hand, the javascript DOM APIs is not that elegant and flexible to be used. 

So Jquery solves the issue of compatibility and also provides elegant and flexible  syntax to operate DOM. 

In one word, Jquery increases front end development efficiency. 

## React, Modularization and No DOM Operation 

React is the mark of modern front end techs. React also marks the new times of front end techs. 

React enables modularization by introducing a powerful object `Component`. 

A `Component` is a reusable module , and can also be integrated into HTML page by using JSX syntax. 

A `component` has input (props) and interal state(state). 

When internal state changes, React enables automatically refresh state onto DOM, which is powered by vitural DOM. 


## Reference 

[Document Object Model](https://en.wikipedia.org/wiki/Document_Object_Model)

[Ajax] (https://en.wikipedia.org/wiki/Ajax_(programming))