import Logo from "./Logo";
import Navigation from "./Navigation";


export default function Header() {
    return (
        <header>
            <div className='header-left'>
                <Logo text="ERNC" />
            </div>
            <div className='header-right'>
                <Navigation></Navigation>
            </div>
        </header>
    )
}