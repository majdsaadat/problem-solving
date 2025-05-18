const xhr = new XMLHttpRequest();
xhr.open("GET", "https://jsonplaceholder.typicode.com/posts");
xhr.responseType = "json";
xhr.send();

let currentPage = 1;
const itemsinPage = 10;

xhr.onload = function() {
  if (xhr.status === 200) {
    const posts = xhr.response;
    const container = document.getElementById('posts-container');
    const nextButton = document.getElementById('Next');
    const Title = document.getElementById('titleP');

    const changeName = posts.map(post => {
      return {
        ...post,
        subject: post.title,
        description: post.body
      };
    });

    function loadPage(page) {
      container.innerHTML = "";  
      const startIndex = (page - 1) * itemsinPage;
      const endIndex = startIndex + itemsinPage;
      const postsToDisplay = changeName.slice(startIndex, endIndex);  

      Title.innerHTML = ` User ID ${currentPage}`;
      
      postsToDisplay.forEach(post => {
        const postElement = document.createElement('div');
        postElement.classList.add('post');

        const titleElement = document.createElement('h2');
        titleElement.textContent = `${post.userId} - ${post.id}`;
        titleElement.style.cursor = "pointer";  

        const detailsElement = document.createElement('div');
        detailsElement.style.display = "none"; 
        detailsElement.innerHTML = `
          <p><strong>Subject:</strong> ${post.subject}</p>  
          <p><strong>Description:</strong> ${post.description}</p>  
        `;

        titleElement.addEventListener('click', function() {
          if (detailsElement.style.display === "none") {
            detailsElement.style.display = "block";
          } else {
            detailsElement.style.display = "none";
          }
        });

        postElement.appendChild(titleElement);
        postElement.appendChild(detailsElement);
        container.appendChild(postElement);
      });

      if (endIndex < changeName.length) {  
        nextButton.style.display = "block";
      } else {
        nextButton.style.display = "none";
      }
    }

    loadPage(currentPage);

    nextButton.addEventListener('click', function() {
      currentPage++;
      loadPage(currentPage);
    });

  } else {
    console.error("An error occurred while fetching data: " + xhr.status);
  }
};

xhr.onerror = function() {
  console.error("Failed to connect to server.");
};
