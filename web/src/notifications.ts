import $ from "jquery";

const notifcationList = $("#notification-list")[0] as HTMLUListElement;

/**
 * Add a notification to the notification list
 * 
 * @param message Message text to display
 * @param className Optional CSS class to apply to the notification (for priority styling)
 */
function notify(message: string, className: string = "") {
  let notif: HTMLLIElement = document.createElement("li");
  notif.innerText = message;
  
  // Add the class for priority-based styling if provided
  if (className) {
    notif.classList.add(className);
  }
  
  notifcationList.insertBefore(notif, notifcationList.firstChild);
  
  // Automatically remove notification after 10 seconds
  setTimeout(() => {
    if (notif.parentNode === notifcationList) {
      notifcationList.removeChild(notif);
    }
  }, 10000);
}

export { notify };
