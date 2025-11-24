# JackieBrowser GitHub Actions Setup

This repository uses GitHub Actions to automatically build JackieBrowser in the cloud.

## ✨ Features

- ✅ Automatic builds on every push to `main`
- ✅ Manual builds via workflow dispatch
- ✅ Automatic releases when you create version tags
- ✅ No local build resources needed
- ✅ Free for public repositories

## 🚀 Quick Start

### 1. Create a GitHub Repository

```bash
# In your JackieBrowser directory
gh repo create JackieBrowser --public --source=. --remote=origin --push
```

Or manually:
1. Go to https://github.com/new
2. Name it "JackieBrowser"
3. Make it public (required for free Actions)
4. Don't initialize with README
5. Click "Create repository"

Then push:
```bash
git remote add origin https://github.com/YOUR_USERNAME/JackieBrowser.git
git branch -M main
git push -u origin main
```

### 2. Trigger a Build

**Option A: Automatic (on push)**
```bash
# Just push any changes
git add .
git commit -m "Update browser"
git push
```

**Option B: Manual trigger**
1. Go to your repo on GitHub
2. Click "Actions" tab
3. Click "Build JackieBrowser" workflow
4. Click "Run workflow"
5. Wait 4-6 hours for build to complete

### 3. Download Your DMG

After build completes:
1. Go to Actions tab
2. Click on the completed workflow run
3. Scroll down to "Artifacts"
4. Download "JackieBrowser-macOS-arm64"

## 📦 Creating Releases

To create an official release with automatic file attachments:

```bash
# Tag your version
git tag -a v1.0.0 -m "JackieBrowser v1.0.0"
git push origin v1.0.0
```

The workflow will:
- Build the browser
- Create a GitHub release
- Attach the DMG automatically

## ⚙️ Customization

### Change Chromium Version

Edit `.github/workflows/build.yml`:
```yaml
env:
  CHROMIUM_VERSION: '133.0.6943.0'  # Change this
```

### Build for Different Architecture

Change the `--arch` flag in the workflow:
- `arm64` - Apple Silicon (M1/M2/M3)
- `x64` - Intel Macs

### Debug Build

Use workflow dispatch and select "debug" as build type.

## 🔍 Monitoring Builds

- **Build time**: ~4-6 hours
- **GitHub gives you**: 2000 free minutes/month for public repos
- **Each build uses**: ~300-400 minutes
- **You can run**: ~5 builds per month free

Check your usage:
- Go to Settings → Billing → Plans and usage
- View Actions minutes used

## ❓ Troubleshooting

### Build fails with "disk space"
- GitHub runners have limited space
- This is a known issue with Chromium builds
- Try using a smaller Chromium version

### Build times out
- Maximum job time is 6 hours
- First build may timeout
- Subsequent builds are faster (cache hits)

### Want faster builds?
- Use self-hosted runners (requires your own server)
- Use paid GitHub Actions minutes
- Build locally with cloud VM (as discussed earlier)

## 📝 Notes

- Builds run on GitHub's macOS runners (free for public repos)
- Each build is independent (no caching between builds)
- First build will take longest (~6 hours)
- Keep repo public to use free Actions
